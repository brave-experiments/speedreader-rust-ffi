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
  void reset(const char* url);
  void pumpContent(const char *content);
  bool finalize(char **transformed);

  ~SpeedReader();

 private:
  SpeedReader(const SpeedReader&) = delete;
  void operator=(const SpeedReader&) = delete;
  C_SpeedReader* raw;
};

}  // namespace speedreader

#endif  // SPEEDREADER_RUST_FFI_SRC_WRAPPER_HPP_
