cmake_minimum_required(VERSION 2.8.9)

add_subdirectory(app)
add_subdirectory(tools)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()