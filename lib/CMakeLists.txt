INCLUDE(ExternalProject)

EXTERNALPROJECT_ADD(
    libconfig
    URL ${CMAKE_CURRENT_SOURCE_DIR}/libconfig-1.4.8.tar.gz
    PREFIX libconfig
    CONFIGURE_COMMAND <SOURCE_DIR>/configure --prefix=<INSTALL_DIR> --disable-examples
    # We patch in order to avoid building the tests.
    # Otherwise compilation will fail due to relative paths used in libconfig.
    PATCH_COMMAND patch < ${CMAKE_CURRENT_SOURCE_DIR}/libconfig.patch
    BUILD_COMMAND make
    INSTALL_COMMAND make install
)


