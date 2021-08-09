FILE(GLOB_RECURSE SRC *.h *.hpp *.cpp *.cc *.c)

add_library(easybot ${SRC})

# how to let the lib auto include?