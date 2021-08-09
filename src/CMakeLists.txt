FILE(GLOB_RECURSE SRC *.h *.hpp *.cpp *.cc *.c)

add_library(easybot ${SRC})
target_include_directories(easybot PUBLIC include)
# how to let the lib auto include?