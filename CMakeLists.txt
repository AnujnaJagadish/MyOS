cmake_minimum_required(VERSION 3.10)

# Set the project name
project(os-simulator C)

# Specify the include directories
include_directories(include)

file(GLOB SOURCES "src/*.c")

# Add the executable
add_executable(os_simulator ${SOURCES})
