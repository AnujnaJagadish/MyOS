# Custom Operating System Code·

This repository contains a simple operating system code written in C, featuring a custom in-memory file system. It demonstrates core OS concepts such as file management, user interaction, concurrency, and synchronization.

## 🔑 Key Features

- **In-memory File System**: Supports basic operations like `create`, `read`, `append`, `rename`, `delete`, and `list`.

- **Thread-safe**: File system is protected by a `mutex`, ensuring mutual exclusion during concurrent operations.

- **Command-line Kernel Simulation**: The `main()` function acts as a user-space kernel, handling system calls and coordinating user input.

- **Concurrency Demonstration**: Multiple threads perform file operations simultaneously to simulate concurrent execution.

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

## 🧑‍💻 Usage

You will be prompted with a command-line interface where you can:

- Create files  
- Read or append to files  
- Rename or delete files  
- List all files  
- Exit the system  


