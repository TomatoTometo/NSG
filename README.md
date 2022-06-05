# NSG

NSG (or Not So Great) is a collection of code that I write to learn algorithms/ideas, C++, C, CMake etc.

This is all done for learning purposes, and thus they are "not so great"

I welcome any suggestions/improvements!


## Extra notes

### MinGW

Version GCC-8.1.0

MinGW acquired from `https://www.mingw-w64.org/`

Better downloaded from `https://sourceforge.net/projects/mingw-w64/files/`

### Gtest
Gtest version used on this project is v1.11.0 (`https://github.com/google/googletest/releases/tag/release-1.11.0`)

Built and installed by the following commands
```bash
mkdir -p build/release
cmake -B build/release/ -G"MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build build/release/
cmake --install build/release/
```


