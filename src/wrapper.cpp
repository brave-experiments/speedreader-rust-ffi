#include "wrapper.hpp"
#include <iostream>
using namespace std;

extern "C" {
#include "lib.h"
}

namespace speedreader {

SpeedReader::SpeedReader(): raw(speedreader_create("")) {}

void SpeedReader::reset(const char* url) {
  raw = speedreader_create(url);
}

void SpeedReader::pumpContent(const char* content) {
  speedreader_pump(raw, content);
}

bool SpeedReader::finalize(std::string* transformed) {
  char* transformed_char_ptr = nullptr;
  bool result = speedreader_finalize(raw, &transformed_char_ptr);
  if (transformed_char_ptr) {
    if (transformed) {
      *transformed = transformed_char_ptr;
    }
    speedreader_c_char_destroy(transformed_char_ptr);
  }
  return result;
}


SpeedReader::~SpeedReader() {}

}  // namespace speedreader
