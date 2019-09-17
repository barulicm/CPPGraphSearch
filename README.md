CPPGraphSearch
==============

Matthew Barulic
2013

A C++ implementation of common graph/tree search algorithms. Currently includes: DFS, BFS, and A*

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

Optionally, to generate HTML documentation in the source directory:

```bash
cmake --build . --target doxygen
```


