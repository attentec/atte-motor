#ifndef FILE_LOADER_H
#define FILE_LOADER_H

#include <string>
#include <vector>

class FileLoader {
public:
  std::vector<std::uint8_t> load_file(string &filename);
};

#endif
