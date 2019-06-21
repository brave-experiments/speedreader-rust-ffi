#ifndef SPEEDREADER_RUST_FFI_SRC_WRAPPER_HPP_
#define SPEEDREADER_RUST_FFI_SRC_WRAPPER_HPP_
#include <memory>
#include <string>
#include <vector>

extern "C" {
#include "lib.h"
}

namespace speedreader {

class SpeedReader {
 public:
  SpeedReader();
  bool process(const std::string& content, const std::string& url,
      std::string *transformed);
  ~SpeedReader();

 private:
  SpeedReader(const SpeedReader&) = delete;
  void operator=(const SpeedReader&) = delete;
};

}  // namespace speedreader

#endif  // SPEEDREADER_RUST_FFI_SRC_WRAPPER_HPP_
