
set(SOURCES
    main.cpp
    cpu.cpp
    inst.cpp
)

set(HEADERS
    cpu.hpp
    inst.hpp
)

add_library(src_library
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(src_library
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC
        ${CMAKE_SOURCE_DIR}/inc
)