cmake_minimum_required(VERSION 2.8.9)

project(cuties)

add_subdirectory(src)
add_subdirectory(font)
add_definitions(-Wall)

set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb ")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O2 -Wall")

#build documentation
option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" ON)
if(BUILD_DOCUMENTATION)

    include(FindDoxygen)
    if(NOT DOXYGEN_FOUND OR NOT DOXYGEN_DOT_FOUND)
      message(FATAL_ERROR
              "Doxygen and Graphviz's dot is needed to build the documentation.")
    endif()

    set( doxyfile_in          ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile     )
    set( doxyfile             ${PROJECT_BINARY_DIR}/Doxyfile              )

    configure_file( ${doxyfile_in} ${doxyfile})

    add_custom_target(doc ALL
                      COMMAND ${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/Doxyfile
                      SOURCES ${PROJECT_BINARY_DIR}/Doxyfile)

    install( DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION share/doc )

endif()

