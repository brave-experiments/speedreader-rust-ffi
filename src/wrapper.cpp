#include "wrapper.hpp"
#include <iostream>
using namespace std;

extern "C" {
#include "lib.h"
}

namespace speedreader {

SpeedReader::SpeedReader() {}

bool SpeedReader::process(const std::string& content, const std::string& url,
    std::string* transformed) {
  char* transformed_char_ptr = nullptr;
  bool result = speedreader_process(content.c_str(), url.c_str(),
    &transformed_char_ptr);
  if (transformed_char_ptr) {
    if (transformed) {
      *transformed = transformed_char_ptr;
    }
    c_char_destroy(transformed_char_ptr);
  }
  return result;
}


SpeedReader::~SpeedReader() {}

}  // namespace speedreader
