cmake_minimum_required(VERSION 3.14)
project(6502_emu VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

add_compile_options(-Wall -Wextra -Wpedantic -g)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)