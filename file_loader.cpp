#include "file_loader.h"
#include <fstream>
#include <iostream>
#include <iterator>

// Load file as binary
std::vector<std::uint8_t> FileLoader::load_file(const std::string &filename) {
  std::ifstream file(filename, std::ios::binary);
  if(file.is_open()) {
    std::istream_iterator<std::uint8_t> file_iterator(file), end;
    std::vector<std::uint8_t> file_data_bytes_vector(file_iterator, end);
    file.close();
    return file_data_bytes_vector;
  } else {
    std::cout << "Unable to open file " << filename << std::endl;
  }
}

Buffer FileLoader::load_file2(const std::string &filename) {
  return file_loading_utils::load_file(filename);
}
