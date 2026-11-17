#include "main.hpp"

#include <cstdint>
#include <filesystem>
#include <iostream>
#include <string>

/// @brief Checks whether the mode string contains the given symbol.
/// @param mode Mode string (e.g. "tn").
/// @param sym Symbol to search for (e.g. 'i').
/// @return true if the symbol is present in mode, false otherwise.
bool checkopt(const std::string& mode, char sym)
{
    std::string opt(1, sym);
    return mode.find(opt) != std::string::npos;
}

/// @brief Maximum allowed source file size (1 GB).
static constexpr uint32_t MAX_FILE_SIZE = 1024 * 1024 * 1024; // 1 GB

/// @brief Runs the fingerprint processing according to the mode.
/// @param mode Mode string with combined option flags.
/// @param fname Source file name.
/// @param offs Offset in bytes from the start of the file.
/// @param length Number of bytes to read (0 — until EOF, max 1 GB).
/// @return Error code (see enErr).
int runproc(const std::string& mode, const std::string& fname, uint32_t offs,
            uint32_t length)
{

    MemArrBlk mblk;
    uint8_t fng[256] = {0};
    Fingerprint printer(fng);

    // Show input parameters
    if (checkopt(mode, 'i'))
    {
        std::cout << "Mode: " << mode << "\n"
                  << "File: " << fname << "\n"
                  << "Offset: " << offs << "\n"
                  << "Length: " << length << "\n";
    }

    // Check source
    if (!fileExists(fname))
        return enErr_srcfile_missed;

    // Check size limits (max 1 GB)
    if (length > MAX_FILE_SIZE)
        return enErr_file_too_big;

    std::error_code ec;
    const std::uintmax_t fileSize = std::filesystem::file_size(fname, ec);
    if (ec || fileSize > MAX_FILE_SIZE)
        return enErr_file_too_big;

    // Try to parse
    if (!mblk.load(fname, offs, length))
        return enErr_srcfile_bounds;

    // Prepare fng[]
    for (std::size_t i = 0; i < mblk.size(); i++)
    {
        uint8_t sym = mblk.data()[i];
        if (!fng[sym])
            fng[sym] = 1;
    }

    // Show results
    if (checkopt(mode, 't'))
    {
        printer.printText();
    }

    if (checkopt(mode, 'n'))
    {
        printer.printHex();
    }

    if (checkopt(mode, 's'))
    {
        printer.printCount();
    }

    if (checkopt(mode, 'j'))
    {
        printer.printJson();
    }

    // Done
    return enErr_ok;
}

/// @brief Application version string.
static constexpr char APP_VERSION[] = "0.1.0";

/// @brief Program entry point.
/// @param argc Number of command line arguments.
/// @param argv Command line arguments.
/// @return EXIT_SUCCESS on success, EXIT_FAILURE on error.
int main(int argc, char *argv[])
{
    // Show usage, version etc ...
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <mode> <file_name> [offset] [length]\n"
                  << "Version: " << APP_VERSION << "\n"
                  << "Modes:\n"
                  << "  i - Show input parameters\n"
                  << "  n - Binary map\n"
                  << "  t - Text map\n"
                  << "  s - Size\n"
                  << "  j - JSON output\n";
        return EXIT_FAILURE;
    }

    if (argc < 3)
    {
        std::cerr << "Error: Missing required arguments.\n"
                  << "Usage: " << argv[0] << " <mode> <file_name> [offset] [length]\n"
                  << "Version: " << APP_VERSION << "\n";
        return EXIT_FAILURE;
    }

    int r = EXIT_SUCCESS;

    try
    {
        auto params = ArgsParser::parse(argc, argv);
        r = runproc(params.mode, params.file_name, params.offset, params.length);
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Error: " << ex.what() << "\n";
        return EXIT_FAILURE;
    }

    return r;
}
