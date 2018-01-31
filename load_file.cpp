#include "load_file.h"
#include <fstream>

// Load file as binary
std::vector<std::uint8_t> LoadFile::load_file(string &filename) {
  std::ifstream file(filename, std::ios::binary);
  std::vector<std::uint8-t> bytes;

  // 
}
