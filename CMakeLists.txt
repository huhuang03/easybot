CMAKE_MINIMUM_REQUIRED(VERSION 3.12)
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

project(easybot)

add_subdirectory(src)
add_subdirectory(test)