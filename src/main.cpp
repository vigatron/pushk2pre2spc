#include "main.hpp"

/// @brief Checks whether the mode string contains the given symbol.
/// @param mode Mode string (e.g. "tn").
/// @param sym Symbol to search for (e.g. 'i').
/// @return true if the symbol is present in mode, false otherwise.
bool checkopt(std::string mode, char sym)
{
    std::string opt(1, sym);
    return mode.find(opt) != std::string::npos;
}

/// @brief Runs the fingerprint processing according to the mode.
/// @param mode Mode string with combined option flags.
/// @param fname Source file name.
/// @param offs Offset in bytes from the start of the file.
/// @param length Number of bytes to read (0 — until EOF).
/// @return Error code (see enErr).
int runproc(std::string mode, std::string fname, uint32_t offs,
            uint16_t length)
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

    // Try to parse
    if (!mblk.load(fname, offs, length))
        return enErr_srcfile_bounds;

    // Prepare fng[]
    for (int i = 0; i < mblk.size(); i++)
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

/// @brief Program entry point.
/// @param argc Number of command line arguments.
/// @param argv Command line arguments.
/// @return EXIT_SUCCESS on success, EXIT_FAILURE on error.
int main(int argc, char *argv[])
{
    // Show usage, version etc ...
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <mode> <file_name> [offset] [length]\n";
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
