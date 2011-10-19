IF(UNIX)
    SET(LIBCONFIG_PREFIX libconfig) 
    SET(LIBCONFIG_PATCH patch < ${CMAKE_CURRENT_SOURCE_DIR}/libconfig.patch)
ENDIF(UNIX)
IF(APPLE)
    SET(LIBCONFIG_PREFIX libconfig/libconfig-1.4.8)    
    SET(LIBCONFIG_PATCH patch -p1 < ${CMAKE_CURRENT_SOURCE_DIR}/test.patch)
ENDIF(APPLE)


INCLUDE(ExternalProject)

EXTERNALPROJECT_ADD(
    libconfig
    URL ${CMAKE_CURRENT_SOURCE_DIR}/libconfig-1.4.8.tar.gz
    PREFIX ${LIBCONFIG_PREFIX}
    PATCH_COMMAND ${LIBCONFIG_PATCH}
    CONFIGURE_COMMAND <SOURCE_DIR>/configure --prefix=<INSTALL_DIR> --disable-examples
    # We patch in order to avoid building the tests.
    # Otherwise compilation will fail due to relative paths used in libconfig.
    BUILD_COMMAND make
    INSTALL_COMMAND make install
)


