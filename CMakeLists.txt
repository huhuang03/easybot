CMAKE_MINIMUM_REQUIRED(VERSION 3.12)


# how did you do this on appveyor?
#message($ENV{VCPKG_ROOT})

if (NOT DEFINED ENV{VCPKG_ROOT})
    message(Please set the vcpkg_root env)
else ()
    if (NOT DEFINED CMAKE_TOOLCHAIN_FILE)
        set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
    endif ()
endif ()

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
# ok let's try the 32 bit

project(easybot)
#message("CMAKE_SIZEOF_VOID_P: ${CMAKE_SIZEOF_VOID_P}")

# ok 32
message("void_p: ${CMAKE_SIZEOF_VOID_P}")
add_subdirectory(src)
add_subdirectory(test EXCLUDE_FROM_ALL)