cmake_minimum_required(VERSION 3.22)

project(peinfo)

add_executable(peinfo
    src/main.c
    src/file_header.c
    src/section_table.c
    src/optional_header.c
    src/data_directories.c
)
set_property(TARGET peinfo PROPERTY
    MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
)
target_compile_definitions(peinfo PRIVATE UNICODE _UNICODE WIN32_LEAN_AND_MEAN)
target_compile_options(peinfo PRIVATE /W4)
