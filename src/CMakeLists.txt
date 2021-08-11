FILE(GLOB_RECURSE SRC *.h *.hpp *.cpp *.cc *.c)

add_library(easybot ${SRC})
target_include_directories(easybot PUBLIC include)

# install target
install(TARGETS easybot)
install(FILES include/util_string.h include/util_window.h DESTINATION include)