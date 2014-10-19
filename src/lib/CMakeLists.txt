# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)

aux_source_directory(. LIB_SRC)

# Tell CMake to create the helloworld executable
add_library(KCLib SHARED ${LIB_SRC})

# Use the Widgets module from Qt 5.
target_link_libraries(KCLib Qt5::Widgets)