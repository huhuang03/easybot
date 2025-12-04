cmake_minimum_required(VERSION 3.14)

project(demo_use_easybot)

find_package(easybot REQUIRED)

add_executable(main main.cc)
target_link_libraries(main easybot::easybot)