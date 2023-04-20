FILE(GLOB_RECURSE
        SRC *.h *.hpp *.cpp *.cc *.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/*.hpp)

#add_library(easybot SHARED ${SRC})
add_library(easybot ${SRC} ../include/easybot/mouse/mouse.h mouse/mouse.cc)

find_package(Boost REQUIRED)

target_include_directories(easybot PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include> $<INSTALL_INTERFACE:include>)

find_package(OpenCV REQUIRED)
target_include_directories(easybot PRIVATE ${OpenCV_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

target_link_libraries(easybot ${OpenCV_LIBS})
if(WIN32)
    target_link_libraries(easybot dwmapi)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    find_library(ApplicationServices ApplicationServices)
    target_link_libraries(easybot ${ApplicationServices})
endif()

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