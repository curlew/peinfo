cmake_minimum_required(VERSION 3.22)

project(peinfo)

add_executable(peinfo src/main.c)
target_compile_definitions(peinfo PRIVATE UNICODE _UNICODE WIN32_LEAN_AND_MEAN)