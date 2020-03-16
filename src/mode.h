#ifndef MODE_H
#define MODE_H
#include <cstddef>

struct Mode {
  size_t vertically, horizontally;
  bool rotated;
  Mode (){}
  Mode (int vertically_, int horizontally_, bool rotated_) :
    vertically(vertically_), horizontally(horizontally_), rotated(rotated_) {
  }
};

#endif // MODE_H
