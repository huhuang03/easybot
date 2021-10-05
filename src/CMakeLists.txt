FILE(GLOB_RECURSE SRC *.h *.hpp *.cpp *.cc *.c)

add_library(easybot ${SRC})

find_package(Boost REQUIRED)

# not work?
target_include_directories(easybot PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include> $<INSTALL_INTERFACE:include>)

find_package(OpenCV REQUIRED)
target_include_directories(easybot PUBLIC ${OpenCV_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

target_link_libraries(easybot ${OpenCV_LIBS} dwmapi)

# install target
install(TARGETS easybot DESTINATION lib EXPORT easybotTargets)
install(EXPORT easybotTargets FILE easybotTargets.cmake DESTINATION lib/cmake/easybot)
# can this emmit?
# how to let cmakeTargets see this include?
install(DIRECTORY ../include/easybot DESTINATION ../include)

include(CMakePackageConfigHelpers)
# generate the config file that is includes the exports
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/easybotConfig.cmake"
        INSTALL_DESTINATION "lib/cmake/easybot"
        NO_SET_AND_CHECK_MACRO
        NO_CHECK_REQUIRED_COMPONENTS_MACRO
        )

# install the configuration file
install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/easybotConfig.cmake
        DESTINATION lib/cmake/easybot)
