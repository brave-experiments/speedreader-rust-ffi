CFLAGS :=

ifdef NDEBUG
CFLAGS += -DNDEBUG=${NDEBUG}
endif

ifdef NO_CXXEXCEPTIONS
CFLAGS += -DNO_CXXEXCEPTIONS=${NO_CXXEXCEPTIONS}
endif

all: examples/cpp.out

src/lib.h: src/lib.rs
	cbindgen -o src/lib.h

sample: examples/cpp.out
	./examples/cpp.out

examples/cpp.out: target/debug/libspeedreader.a examples/wrapper.o examples/cpp/main.cpp 
	g++ $(CFLAGS) -std=gnu++0x examples/cpp/main.cpp examples/wrapper.o ./target/debug/libspeedreader.a -I ./src -lpthread -ldl -o examples/cpp.out

examples/wrapper.o: src/lib.h src/wrapper.cpp src/wrapper.hpp
	g++ $(CFLAGS) -std=gnu++0x src/wrapper.cpp -I src/ -c  -o examples/wrapper.o

target/debug/libspeedreader.a: src/lib.rs Cargo.toml
	cargo build

valgrind-supp: sample
	valgrind --gen-suppressions=all --suppressions=.valgrind.supp  --leak-check=yes --error-exitcode=1 ./examples/cpp.out --gen-suppressions=all

valgrind: sample
	valgrind -v --suppressions=.valgrind.supp  --leak-check=yes --error-exitcode=1 ./examples/cpp.out --gen-suppressions=all

clean:
	rm -rf target

lint:
	cargo fmt -- --check
	cargo clippy
