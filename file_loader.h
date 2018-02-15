#ifndef FILE_LOADER_H
#define FILE_LOADER_H

#include <string>
#include <vector>
#include "buffer.h"

#include "file_loading_utils.h"

class FileLoader {
public:
  std::vector<std::uint8_t> load_file(const std::string &filename);
  Buffer load_file2(const std::string &filename);
};

#endif
