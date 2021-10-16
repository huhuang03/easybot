# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

# can I pass the string meta programming?

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

    gtest_discover_tests(${name})
endfunction()

add_test(test_util_window)
add_test(test_window)
add_test(test_process)
add_test(test_hsv_range)