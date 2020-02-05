#ifndef SPEEDREADER_RUST_FFI_H
#define SPEEDREADER_RUST_FFI_H

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct C_SpeedReader C_SpeedReader;

/**
 * Destroy a `*c_char` once you are done with it.
 */
void speedreader_c_char_destroy(char *s);

/**
 * Create a new `SpeedReader instance`.
 */
C_SpeedReader *speedreader_create(const char *url);

/**
 * Create a new `SpeedReader` instance.
 */
bool speedreader_finalize(C_SpeedReader *speedreader, char **transformed);

/**
 * Append more data to the document being processed
 */
void speedreader_pump(C_SpeedReader *speedreader, const char *content);

#endif /* SPEEDREADER_RUST_FFI_H */
