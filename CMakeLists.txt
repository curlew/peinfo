cmake_minimum_required(VERSION 3.22)

project(peinfo)

add_executable(peinfo
    src/main.c
    src/file_header.c
    src/section_table.c
    src/optional_header.c
    src/import_table.c
)

target_compile_definitions(peinfo PRIVATE UNICODE _UNICODE WIN32_LEAN_AND_MEAN)
