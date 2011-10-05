
INCLUDE(ExternalProject)

EXTERNALPROJECT_ADD(
    libconfig
    URL ${CMAKE_CURRENT_SOURCE_DIR}/libconfig.tar.gz
    PREFIX libconfig
    CONFIGURE_COMMAND <SOURCE_DIR>/configure --prefix=<INSTALL_DIR>
    BUILD_COMMAND make
    INSTALL_COMMAND make install
)


