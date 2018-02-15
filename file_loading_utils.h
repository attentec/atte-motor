#ifndef FILE_LOADING_UTILS_H
#define FILE_LOADING_UTILS_H

#include <string>
#include "buffer.h"

namespace file_loading_utils {

Buffer load_file(const std::string& filename);
}

#endif
