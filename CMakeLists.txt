CMAKE_MINIMUM_REQUIRED(VERSION 3.12)

# how to fix the clion auto set env??
message("$ENV{VCPKG_ROOT}")

if(NOT DEFINED ENV{VCPKG_ROOT})
    message(Please set the vcpkg_root env)
else()
    if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
        set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
    endif()
endif()

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

project(easybot)

add_subdirectory(src)
add_subdirectory(test EXCLUDE_FROM_ALL)
