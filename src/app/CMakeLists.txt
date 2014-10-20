find_package(PythonLibs 3 REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

aux_source_directory(. APP_SRC)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

add_executable(${PROJECT_NAME} ${APP_SRC})
target_link_libraries(${PROJECT_NAME} ${PYTHON_LIBRARY})

configure_file(main.py ${PROJECT_BINARY_DIR} COPYONLY)
