set(testname "kchighlightertest")
set(app_dir "../../app")

find_package(Qt5Widgets)
include_directories(${app_dir})
set(${testname}_additional
    ${app_dir}/kchighlighter.cpp
    ${app_dir}/kctextblockdata.cpp)
set(CMAKE_AUTOMOC ON)
add_executable(${testname} "tst_${testname}.cpp" ${${testname}_additional})
qt5_use_modules(${testname} Widgets Test)

add_test(${testname} ${testname})
