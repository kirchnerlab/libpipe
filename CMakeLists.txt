PROJECT(MSTK)

# require at least cmake 2.6
cmake_minimum_required(VERSION 2.6)
# include macro definitions
INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/cmake/macros/require_out_of_src_build.cmake)
SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

#############################################################################
# build libraries
#############################################################################

# require out-of-source build
MACRO_REQUIRE_OUT_OF_SRC_BUILD("MSTK requires out-of-source builds.")

#SET(CMAKE_CXX0X_FLAGS "-std=c++0x" )
# more warnings against everything
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wconversion -Wall " )
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX0X_FLAGS}" )

CONFIGURE_FILE(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/mstk/config.hpp.cmake 
    ${MSTK_BINARY_DIR}/include/mstk/config.hpp
)

# add subdirs
OPTION(ENABLE_TESTING "Compile tests" ON)
OPTION(ENABLE_COVERAGE "Enable GCov coverage analysis (defines a 'coverage' target and enforces static build of ms++)" OFF)
OPTION(ENABLE_BENCHMARK "Do benchmarking and plotting" ON)
OPTION(ENABLE_EXAMPLES "Compile examples" ON)

# require boost
SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD OFF)
FIND_PACKAGE(Boost COMPONENTS program_options system REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

# global include dirs
INCLUDE_DIRECTORIES(
    ${MSTK_SOURCE_DIR}/include
    ${MSTK_BINARY_DIR}/include
)

# build lib
ADD_SUBDIRECTORY(src)

#############################################################################
# syncing docs
#############################################################################
#ADD_CUSTOM_TARGET(syncdocs COMMAND ${MSTK_SOURCE_DIR}/scripts/sync-docs-gh-pages.sh ${MSTK_SOURCE_DIR} ${MSTK_BINARY_DIR})
#ADD_DEPENDENCIES(syncdocs doc)

#############################################################################
# regression tests
#############################################################################
#SET(UPDATE_TYPE git)
#IF (ENABLE_TESTING)
#  INCLUDE(CTest)
#  ENABLE_TESTING()
#  ADD_SUBDIRECTORY(test)
#ENDIF (ENABLE_TESTING)

#############################################################################
# code coverage analysis
#############################################################################
#IF (ENABLE_COVERAGE)
#    SET (ENABLE_EXAMPLES ON)
#    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
#    CONFIGURE_FILE(${MSTK_SOURCE_DIR}/cmake/scripts/coverage.sh.in
#        ${MSTK_BINARY_DIR}/cmake/scripts/coverage.sh
#        @ONLY IMMEDIATE
#    )
#    CONFIGURE_FILE(${MSTK_SOURCE_DIR}/cmake/scripts/unit_coverage.sh.in
#        ${MSTK_BINARY_DIR}/cmake/scripts/unit_coverage.sh
#        @ONLY IMMEDIATE
#    )
#    ADD_CUSTOM_TARGET(
#        coverage COMMAND /bin/bash ${MSTK_BINARY_DIR}/cmake/scripts/coverage.sh
#    )
#ENDIF(ENABLE_COVERAGE)


############################################################################
# examples
############################################################################
IF (ENABLE_EXAMPLES)
    ADD_SUBDIRECTORY(examples)
ENDIF (ENABLE_EXAMPLES)

#############################################################################
# documentation
#############################################################################
# doxygen support
CONFIGURE_FILE(${MSTK_SOURCE_DIR}/doc/Doxyfile.cmake
    ${MSTK_BINARY_DIR}/doc/Doxyfile
    @ONLY IMMEDIATE
    )
FIND_PACKAGE(Doxygen)

# target for doxygen
ADD_CUSTOM_TARGET(doc COMMAND ${DOXYGEN} ${MSTK_BINARY_DIR}/doc/Doxyfile)

##############################################################################
## installation
##############################################################################
## location, location, location
#IF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
#SET(CMAKE_INSTALL_PREFIX
#"/usr/local" CACHE PATH "libfbi install prefix" FORCE
#)
#ENDIF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
## headers
#INSTALL(DIRECTORY ${MSTK_SOURCE_DIR}/include/fbi
#    DESTINATION include
#    COMPONENT headers
#    REGEX "/.git$" EXCLUDE
#    PATTERN "config.h.cmake" EXCLUDE)
#
## config.h
#INSTALL(FILES ${MSTK_BINARY_DIR}/include/fbi/config.h
#    DESTINATION include/fbi
#    COMPONENT headers)
#
## documentation
#INSTALL(DIRECTORY ${MSTK_BINARY_DIR}/doc
#    DESTINATION share/fbi
#    COMPONENT documentation
#    PATTERN "Doxyfile" EXCLUDE)
#
##############################################################################
## packaging
##############################################################################
## FIXME: make sure that the documentation is compiled and pdfs are 
##        generated prior to packaging!
#
#set(CPACK_PACKAGE_NAME "libfbi")
#set(CPACK_PACKAGE_VENDOR "steenlab.org")
#set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Fast Box Intersection library")
#
## CPack version strings
#SET(CPACK_PACKAGE_VERSION_MAJOR ${VERSION_MAJOR})
#SET(CPACK_PACKAGE_VERSION_MINOR ${VERSION_MINOR})
#SET(CPACK_PACKAGE_VERSION_PATCH ${VERSION_PATCH})
#
#SET(CPACK_RESOURCE_FILE_README "${MSTK_SOURCE_DIR}/README.txt")
#SET(CPACK_RESOURCE_FILE_LICENSE "${MSTK_SOURCE_DIR}/LICENSE.txt")
#
#set(CPACK_COMPONENTS_ALL libraries headers applications documentation)
#set(CPACK_COMPONENT_LIBRARIES_DISPLAY_NAME "Libraries")
#set(CPACK_COMPONENT_HEADERS_DISPLAY_NAME "C++ Development Headers")
#set(CPACK_COMPONENT_DOCUMENTATION_DISPLAY_NAME "C++ Interface Documentation")
#
#set(CPACK_COMPONENT_LIBRARIES_DESCRIPTION
#    "Compiled libraries for fast box intersection.")
#set(CPACK_COMPONENT_HEADERS_DESCRIPTION
#    "C++ header files for libfbi development.")
#set(CPACK_COMPONENT_DOCUMENTATION_DESCRIPTION
#    "The C++ libfbi interface documentation (Doxygen).")
#
#INCLUDE(CPack)
#
