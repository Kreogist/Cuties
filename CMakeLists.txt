cmake_minimum_required(VERSION 2.8.9)

project(cuties)

set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb ")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O2 -Wall")

#check C++11 support
include(cxx11.cmake)
check_for_cxx11_compiler(CXX11_COMPILER)
# If a C++11 compiler is available, then set the appropriate flags
if(CXX11_COMPILER)
    enable_cxx11()
else(CXX11_COMPILER)
    MESSAGE(FATAL_ERROR "Can not enable C++11 support.")
endif(CXX11_COMPILER)

add_subdirectory(src)
add_subdirectory(font)
add_definitions(-Wall)

#build unit test
option(BUILD_TESTS "Build unit tests" OFF)
if(BUILD_TESTS)
    enable_testing()
endif()

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

    install( DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc/html DESTINATION ${PROJECT_NAME}/doc/html )

endif()

#build package
option(BUILD_DEB_PACKAGE "Create DEB Package" OFF)
if(BUILD_DEB_PACKAGE)
	set(BUILD_PACKAGE ON)
    set(CPACK_GENERATOR ${CPACK_GENERATOR} "DEB")
endif()

option(BUILD_NSIS_PACKAGE "Create NSIS Package" OFF)
if(BUILD_NSIS_PACKAGE)
	set(BUILD_PACKAGE ON)
    set(CPACK_GENERATOR ${CPACK_GENERATOR} "NSIS")
endif()

option(BUILD_RPM_PACKAGE "Create RPM Package" OFF)
if(BUILD_RPM_PACKAGE)
	set(BUILD_PACKAGE ON)
    set(CPACK_GENERATOR ${CPACK_GENERATOR} "RPM")
endif()

option(BUILD_TGZ_PACKAGE "Create TGZ pakage" ON)
if(BUILD_TGZ_PACKAGE)
	set(BUILD_PACKAGE ON)
    set(CPACK_GENERATOR ${CPACK_GENERATOR} "TGZ")
endif()

if(BUILD_PACKAGE)
	set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A Smart IDE written by Qt")
	set(CPACK_PACKAGE_VENDOR "Kreogist Dev Team")
	set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
	set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
	set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/licenses/LICENSE_GPL.txt")
	set(CPACK_PACKAGE_VERSION_MAJOR "0")
	set(CPACK_PACKAGE_VERSION_MINOR "2")
	set(CPACK_PACKAGE_VERSION_PATCH "1.0")
	set(CPACK_PACKAGE_INSTALL_DIRECTORY "Kreogist/${PROJECT_NAME}.${CPACK_PACKAGE_VERSION_MAJOR}")
    INCLUDE(CPack)
endif()
