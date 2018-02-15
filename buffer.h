#ifndef BUFFER_H
#define BUFFER_H

#include <cstdint>
#include <exception>

struct Buffer {
  std::uint8_t* data;
  std::size_t size;
  std::uint8_t operator[] (std::size_t index) {
    if (index < size) {
      return data[index];
    }
    std::terminate(); // fuck yo shit
  }
};

#endif
