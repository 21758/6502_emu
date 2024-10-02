
add_executable(6502_test
    test.cpp
    test.hpp
)

target_link_libraries(6502_test
    PRIVATE
        gtest_main
        src_library
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 
    ${CMAKE_BINARY_DIR}/bin
)

include(GoogleTest)
gtest_discover_tests(6502_test)