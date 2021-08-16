CMAKE_MINIMUM_REQUIRED(VERSION 3.12)

# why you add the prefix
# and c:/Program Files/${PROJECT_NAME} on Windows
#message("CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

project(easybot)

message("CMAKE_GENERATOR: ${CMAKE_GENERATOR}")
message("CMAKE_SIZEOF_VOID_P: ${CMAKE_SIZEOF_VOID_P}")
message("arch_hint: ${arch_hint}")
# but why you default to install E:/Program Files?

add_subdirectory(src)
add_subdirectory(test EXCLUDE_FROM_ALL)