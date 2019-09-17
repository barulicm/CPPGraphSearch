GraphSearch
==============

A C++ implementation of common graph/tree search algorithms.

You can see full documentation at http://barulicm.github.io/CPPGraphSearch.

## Installation

```bash
mkdir build
cd build
cmake ..
sudo cmake --build . --target install
```

Optionally, to build and run the test suite:

```bash
cmake --build . --target run_tests
```

Optionally, to build the included examples:

```bash
cmake --build . --target examples
```

Optionally, to generate HTML documentation in the build directory:

```bash
cmake --build . --target doxygen
```

## Usage in a CMake Project

Once installed, the easiest way to use this library is from within a CMake 
project. 

Simply find the package `GraphSearch` ...

```cmake
find_package(GraphSearch)
```

... and link to the imported target `GraphSearch::GraphSearch`.

```cmake
target_link_libraries(<target_name> GraphSearch::GraphSearch)
``` 
