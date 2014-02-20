
if(CPACK_GENERATOR MATCHES "NSIS")

endif()

if(CPACK_GENERATOR MATCHES "DEB")
    set(CPACK_DEBIAN_PACKAGE_DEPENDS "libstdc++6 (>=4.4.0), libqt5core5 (>= 5.2.0), libqt5gui5 (>= 5.2.0), libqt5widgets5 (>= 5.2.0)")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Wang Luming<wlm199558@126.com>")
endif()