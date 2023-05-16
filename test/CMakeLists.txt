# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
    cmake_policy(SET CMP0135 NEW)
endif()
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/master.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()
include(GoogleTest)

function(add_test name)
    add_executable(
            ${name}
            ${name}.cc
            util_test.cc
    )

    target_link_libraries(
            ${name}
            gtest_main
            easybot
    )
    target_include_directories(${name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)

    gtest_discover_tests(${name})
endfunction()

add_test(test_util_window)
add_test(test_window)
add_test(test_process)
add_test(test_hsv_range)