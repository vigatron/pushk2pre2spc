#include "main.hpp"

//
bool checkopt(std::string mode, char sym) {
  std::string opt(1, sym);
  return mode.find(opt) != std::string::npos;
}

//
int runproc(std::string mode, std::string fname, uint32_t offs,
            uint16_t length) {

  MemArrBlk mblk;
  uint8_t fng[256] = {0};

  // Show input parameters
  if (checkopt(mode, 'i')) {
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
  for (int i = 0; i < mblk.size(); i++) {
    uint8_t sym = mblk.data()[i];
    if (!fng[sym])
      fng[sym] = 1;
  }

  // Show results
  if (checkopt(mode, 't')) {
    showresults_t(fng);
  }

  if (checkopt(mode, 'n')) {
    showresults_n(fng);
  }

  if (checkopt(mode, 's')) {
    showresults_s(fng);
  }

  // Done
  return enErr_ok;
}

//
int main(int argc, char *argv[]) {

  int r = EXIT_SUCCESS;

  try {
    auto params = ArgsParser::parse(argc, argv);
    r = runproc(params.mode, params.file_name, params.offset, params.length);
  } catch (const std::exception &ex) {
    std::cerr << "Error: " << ex.what() << "\n";
    return EXIT_FAILURE;
  }

  return r;
}
