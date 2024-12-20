cmake_minimum_required(VERSION 3.10)
project(Experiments)

set(CMAKE_C_COMPILER_VERSION 11)
set(CMAKE_C_FLAGS "-Wextra -Wall -Wpedantic -O2")

add_executable(exec
    "src/main.c"
)

