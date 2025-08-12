# OS Simulator·

This repository contains a simple in-memory file system implementation in C.

File system is mutally exclusive (protected by mutex), hence any concurrent operations are
executed sequentially and not in any order.

Kernel is simulated from the `main()` function which orchestrates user interaction with
the file system.


## Building the project

This repository is tested on Linux-x86_64 and MacOS_x86_64 (Mac Intel) with following dependencies
- gcc (GCC) 15.1.1·

The root of the project contains `CMakeLists.txt` file.·

Execute the following from root of the project:

```
mkdir -p build && cd build
cmake ..
make
```

this will create an executable *os_simulator* in the build directory inside root.

Run `./os_simulator` to start the program.
