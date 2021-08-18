CMAKE_MINIMUM_REQUIRED(VERSION 3.12)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
# ok let's try the 32 bit

project(easybot)

#message("CMAKE_GENERATOR: ${CMAKE_GENERATOR}")
#message("CMAKE_SIZEOF_VOID_P: ${CMAKE_SIZEOF_VOID_P}")
#message("CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")
# but why you default to install E:/Program Files?

add_subdirectory(src)
add_subdirectory(test EXCLUDE_FROM_ALL)