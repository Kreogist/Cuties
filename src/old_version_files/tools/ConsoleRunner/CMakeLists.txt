cmake_minimum_required(VERSION 2.8.9)

set(SRC_LIST main.cpp)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

add_executable(KciConsoleRunner ${SRC_LIST})

set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS ON)
if(CMAKE_SYSTEM_NAME STREQUAL Linux)
    add_definitions(-D_OS_LINUX_)
    message("Building on Linux")
elseif(WIN32)
    add_definitions(-D_OS_WIN32_)
    message("Building on Windows")
elseif(APPLE)
    add_definitions(-D_OS_MAC_X_)
    message("Building on Apple")
endif()

#install
install(TARGETS KciConsoleRunner
        DESTINATION ${PROJECT_NAME})
