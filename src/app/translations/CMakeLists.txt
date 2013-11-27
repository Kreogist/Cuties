cmake_minimum_required(VERSION 2.8.9)

set(TRANSLATIONS_LIST en_US.ts)
set(TRANSLATIONS_LIST ${TRANSLATIONS_LIST} zh_CN.ts)

find_package(Qt5LinguistTools)
if(Qt5LinguistTools_FOUND)
qt5_add_translation(${PROJECT_BINARY_DIR}/Locale ${TRANSLATIONS_LIST})
endif(Qt5LinguistTools_FOUND)

configure_file(Locale.db ${PROJECT_BINARY_DIR}/Locale/Locale.db COPYONLY)
