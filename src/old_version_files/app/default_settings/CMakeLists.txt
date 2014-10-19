configure_file(default.style ${PROJECT_BINARY_DIR}/default.style COPYONLY)
configure_file(DefaultColorConfig.ini ${PROJECT_BINARY_DIR}/DefaultColorConfig.ini COPYONLY) 
if(WIN32)
    configure_file(Cuties_Win32.ini ${PROJECT_BINARY_DIR}/Cuties.ini COPYONLY)
else(WIN32)
    configure_file(Cuties_Unix.ini ${PROJECT_BINARY_DIR}/Cuties.ini COPYONLY)
endif(WIN32)


install(FILES default.style DefaultColorConfig.ini
        DESTINATION ${PROJECT_NAME})