add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

FILE(GLOB_RECURSE
        SRC *.h *.hpp *.cpp *.cc *.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/*.hpp)

#add_library(easybot SHARED ${SRC})
add_library(easybot ${SRC} ../include/easybot/mouse/mouse.h mouse/mouse.cc)

#find_package(Boost REQUIRED)

target_include_directories(easybot PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include> $<INSTALL_INTERFACE:include>)

find_package(OpenCV CONFIG REQUIRED)
#find_package(OpenCV REQUIRED)
target_include_directories(easybot PRIVATE ${OpenCV_INCLUDE_DIRS})

target_link_libraries(easybot ${OpenCV_LIBS})
if(WIN32)
    target_link_libraries(easybot dwmapi)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    find_library(ApplicationServices ApplicationServices)
    target_link_libraries(easybot ${ApplicationServices})
endif()

# install target
# ok do the install info
include(GNUInstallDirs)
if (BUILD_SHARED_LIBS AND MSVC)
    target_compile_definitions(easybot PRIVATE MYLIB_EXPORTS)
endif ()
install(TARGETS easybot
        EXPORT easybot_targets
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
)

install(DIRECTORY "${CMAKE_SOURCE_DIR}/include/" DESTINATION include)

install(EXPORT easybot_targets
FILE easybot-targets.cmake
NAMESPACE easybot::
DESTINATION share/easybot)

file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/easybot-config.cmake"
"include(CMakeFindDependencyMacro)\n"
"find_dependency(opencv CONFIG REQUIRED)\n"
"include(\"\${CMAKE_CURRENT_LIST_DIR}/easybot-targets.cmake\")\n")
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/easybot-config.cmake"
    DESTINATION share/easybot)