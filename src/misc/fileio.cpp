#include "fileio.hpp"

bool fileExists(const std::string &path) {
  try {
    return std::filesystem::exists(path) &&
           std::filesystem::is_regular_file(path);
  } catch (const std::filesystem::filesystem_error &e) {
    std::cerr << "Access error: " << e.what() << '\n';
    return false;
  }
}
