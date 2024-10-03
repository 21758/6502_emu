find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

add_executable(M6502_test
    test.cpp
    test.hpp
)

target_link_libraries(M6502_test
    PRIVATE
    GTest::GTest 
    GTest::Main
    Threads::Threads
    src_library
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 
    ${CMAKE_BINARY_DIR}/bin
)

include(GoogleTest)
gtest_discover_tests(M6502_test)