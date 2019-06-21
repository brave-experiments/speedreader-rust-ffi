
**A FFI crate C++ wrapper to expose functionality from [SpeedReader](https://github.com/brave-experiments/speedreader)**

The `speedreader` crate implements a currently simple appraoch to performing HTML content readability detection and transformation.
This crate exposes C FFI functions and is configured to produce a static library so that the functionality can be used in other languages.

Currently there are only bindings for C++.

# Development

Working on this repository requires having Rust, g++, and valgrind installed.

## Testing

There are end to end test binaries for C++ bindings, when run under
valgrind we can ensure memory is being properly freed.

## C++

### Running tests

```
make sample
```

## Regenerating the C header

```
cbindgen -o src/lib.h
```
