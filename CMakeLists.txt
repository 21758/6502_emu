cmake_minimum_required(VERSION 3.10)
project(6502_emu VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED true)

add_compile_options(-Wall -Wextra -Wpedantic)

add_subdirectory(src)