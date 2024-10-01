
set(SOURCES
    main.cpp
    cpu.cpp
    inst.cpp
)

set(HEADERS
    cpu.hpp
    inst.hpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 
    ${CMAKE_BINARY_DIR}/bin
)

add_executable(6502_emu ${SOURCES} ${HEADERS})

target_include_directories(6502_emu
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC
        ${CMAKE_SOURCE_DIR}/inc
)