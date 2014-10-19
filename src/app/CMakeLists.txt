set(Python_ADDITIONAL_VERSIONS 3.4)

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

aux_source_directory(. APP_SRC)

add_executable(${PROJECT_NAME} ${APP_SRC})
