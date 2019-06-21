#ifndef SPEEDREADER_RUST_FFI_H
#define SPEEDREADER_RUST_FFI_H

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/**
 * Destroy a `*c_char` once you are done with it.
 */
void c_char_destroy(char *s);

/**
 * Create a new `SpeedReader` instance.
 */
bool speedreader_process(const char *content, const char *url, char **transformed);

#endif /* SPEEDREADER_RUST_FFI_H */
