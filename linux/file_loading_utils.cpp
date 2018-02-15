
#include "../file_loading_utils.h"

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

namespace file_loading_utils {

Buffer load_file(const std::string& filename) {
  int file_descriptor = open(filename.c_str(), O_RDONLY);
  struct stat d;
  fstat(file_descriptor, &d);
  void* data = mmap(NULL, d.st_size, PROT_READ, MAP_SHARED, file_descriptor, 0);

  Buffer b;
  b.data = (uint8_t*)data;
  b.size = d.st_size;
  return b;

}

}
