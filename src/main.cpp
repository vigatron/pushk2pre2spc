#include "main.hpp"

// Global variables
uint8_t fng[256] = {0};

//
int runproc(std::string mode, std::string fname, uint32_t offs,
            uint16_t length) {

  MemArrBlk mblk;

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
    showresults_t();
  }

  if (checkopt(mode, 'n')) {
    showresults_n();
  }

  // Done
  return enErr_ok;
}

//

int main(int argc, char *argv[]) {

  int r = EXIT_SUCCESS;

  try {

    auto params = ArgsParser::parse(argc, argv);

    if (checkopt(params.mode, 'i')) {

      std::cout << "Mode: " << params.mode << "\n"
                << "File: " << params.file_name << "\n"
                << "Offset: " << params.offset << "\n"
                << "Length: " << params.length << "\n";
    }

    r = runproc(params.mode, params.file_name, params.offset, params.length);

  } catch (const std::exception &ex) {
    std::cerr << "Error: " << ex.what() << "\n";
    return EXIT_FAILURE;
  }

  return r;
}

bool checkopt(std::string mode, char sym) {
  std::string opt(1, sym);
  return mode.find(opt) != std::string::npos;
}

//
void showresults_t() {

  for (int i = 0; i < 256; i++) {
    uint8_t v = fng[i] ? '#' : '.';
    bool sep = (i % 16) == 15;
    std::cout << v;
    if (sep)
      std::cout << '\n';
  }
}

const char szHEX[] = "0123456789ABCDEF";

//
void showresults_n() {
  uint8_t cmplx[32] = {0};
  for (int i = 0; i < 256; i++) {
    uint8_t bpos = i >> 3;
    uint8_t mask = 1 << 7 - (i % 8);
    if (fng[i]) {
      cmplx[bpos] |= mask;
    }
  }

  for (int i = 0; i < 32; i++) {
    uint8_t v = cmplx[i];
    std::cout << szHEX[(v >> 4) & 0xF] << szHEX[v & 0xF];
  }
  std::cout << "\n";
}
