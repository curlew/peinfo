cmake_minimum_required(VERSION 3.22)

project(peinfo VERSION 1.1.0)

add_executable(peinfo
    src/main.c
    src/characteristics.c
    src/utils.c
    src/file_header.c
    src/section_table.c
    src/optional_header.c
    src/data_directories.c
)
set_target_properties(peinfo
    PROPERTIES
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
        OUTPUT_NAME "peinfo-${PROJECT_VERSION}"
)
target_compile_definitions(peinfo PRIVATE UNICODE _UNICODE WIN32_LEAN_AND_MEAN)
target_compile_options(peinfo PRIVATE /W4)
