PROJECT(LIBPIPE)

# require at least cmake 2.8
cmake_minimum_required(VERSION 2.8)

#############################################################################
# include cmake scripts
#############################################################################
SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/macros)

# require out-of-source build
INCLUDE(require_out_of_src_build)
MACRO_REQUIRE_OUT_OF_SRC_BUILD("LIBPIPE requires out-of-source builds.")

# Git revision saved in variable LIBPIPE_VERSION
INCLUDE(GetGitRevisionDescription)
get_git_head_revision(GIT_REFSPEC LIBPIPE_VERSION)

#############################################################################
# Varaibles to upper string for easier comparisions
#############################################################################

STRING(TOUPPER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE)

#############################################################################
# build libraries
#############################################################################
# require boost
SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD OFF)
#make sure that at least version 1.46.0 is used
SET(BOOST_MIN_VERSION "1.46.0")
FIND_PACKAGE(Boost ${BOOST_MIN_VERSION} COMPONENTS thread REQUIRED)

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

#############################################################################
# compiler Flags
#############################################################################

# Set default compile flags for GCC
if(CMAKE_COMPILER_IS_GNUCXX)
    SET(CMAKE_CXX_FLAGS_DEBUG  "-O0 -Wall -Wconversion -ggdb3 -D_FILE_OFFSET_BITS=64")
    SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -ftree-vectorize -msse2")
    SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g -O3")
endif(CMAKE_COMPILER_IS_GNUCXX)



#############################################################################
# Cmake generated header files
#############################################################################
CONFIGURE_FILE(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/libpipe/config.hpp.cmake 
    ${LIBPIPE_BINARY_DIR}/include/libpipe/config.hpp
)

#############################################################################
# Cmake Options
#############################################################################

OPTION(ENABLE_TESTING "Compile tests" ON)
OPTION(ENABLE_COVERAGE "Enable GCov coverage analysis (defines a 'coverage' target and enforces static build of libpipe)" OFF)
OPTION(ENABLE_EXAMPLES "Compile examples" OFF)
OPTION(ENABLE_THREADING "Enable threading" FALSE)

#############################################################################
# global include dirs
#############################################################################

INCLUDE_DIRECTORIES(
    ${LIBPIPE_SOURCE_DIR}/include
    ${LIBPIPE_BINARY_DIR}/include
)

#############################################################################
# messages and error handling
#############################################################################
MESSAGE(STATUS "Libpipe Git Commit: "${LIBPIPE_VERSION})
MESSAGE(STATUS "Build type: "${CMAKE_BUILD_TYPE})
MESSAGE(STATUS "CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}")
IF(ENABLE_THREADING)
    MESSAGE(STATUS "Threading enabled")
ELSE()
    MESSAGE(STATUS "Threading disabled")   
ENDIF()
IF(ENABLE_TESTING)
    MESSAGE(STATUS "Testing enabled")
ELSE()
    MESSAGE(STATUS "Testing disabled")
ENDIF()
IF(ENABLE_EXAMPLES)
    MESSAGE(STATUS "Examples enabled")
ELSE()
    MESSAGE(STATUS "Examples disabled")
ENDIF()
IF (ENABLE_COVERAGE)
    IF(CMAKE_BUILD_TYPE STREQUAL "DEBUG" AND ENABLE_TESTING)
        MESSAGE(STATUS "Coverage enabled")
    ELSEIF(NOT ENABLE_TESTING)
        MESSAGE(FATAL_ERROR "Coverage analysis requires Testing Enabled")
    ELSE()
        MESSAGE(FATAL_ERROR "Coverage analysis requires DEBUG build")
    ENDIF()
ELSE()
    MESSAGE(STATUS "Coverage disabled")
ENDIF()


#############################################################################
# code coverage analysis
#############################################################################

IF (ENABLE_COVERAGE)
    IF(CMAKE_BUILD_TYPE STREQUAL "DEBUG" AND ENABLE_TESTING)
        SET (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage")
        CONFIGURE_FILE(${LIBPIPE_SOURCE_DIR}/cmake/scripts/coverage.sh.in
            ${LIBPIPE_BINARY_DIR}/cmake/scripts/coverage.sh
            @ONLY IMMEDIATE
        )
        ADD_CUSTOM_TARGET(
            coverage COMMAND /bin/bash ${LIBPIPE_BINARY_DIR}/cmake/scripts/coverage.sh
        )        
    ENDIF()
ENDIF(ENABLE_COVERAGE)


#############################################################################
# tests
#############################################################################

IF (ENABLE_TESTING)
  INCLUDE(CTest)
  ENABLE_TESTING()
  ADD_SUBDIRECTORY(test)
ENDIF (ENABLE_TESTING)


#############################################################################
# build libpipe
#############################################################################

ADD_SUBDIRECTORY(src)

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
CONFIGURE_FILE(${LIBPIPE_SOURCE_DIR}/doc/Doxyfile.cmake
    ${LIBPIPE_BINARY_DIR}/doc/Doxyfile
    @ONLY IMMEDIATE
    )
CONFIGURE_FILE(${LIBPIPE_SOURCE_DIR}/doc/libpipe.png
    ${LIBPIPE_BINARY_DIR}/doc/html/libpipe.png
    COPYONLY
    )
FIND_PACKAGE(Doxygen)

# target for doxygen
ADD_CUSTOM_TARGET(doc COMMAND ${DOXYGEN} ${LIBPIPE_BINARY_DIR}/doc/Doxyfile)

#############################################################################
# installation
#############################################################################
# location, location, location
IF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
SET(CMAKE_INSTALL_PREFIX
"/usr/local" CACHE PATH "libpipe install prefix" FORCE
)
ENDIF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
# so that the dmg works also to the given location
SET(CPACK_PACKAGE_DEFAULT_LOCATION ${CMAKE_INSTALL_PREFIX})


# headers
INSTALL(DIRECTORY ${LIBPIPE_SOURCE_DIR}/include/libpipe
    DESTINATION include
    COMPONENT headers
    REGEX "/.git$" EXCLUDE
    PATTERN "config.hpp.cmake" EXCLUDE)

# config.h
INSTALL(FILES ${LIBPIPE_BINARY_DIR}/include/libpipe/config.hpp
    DESTINATION include/libpipe
    COMPONENT headers)

# documentation
INSTALL(DIRECTORY ${LIBPIPE_BINARY_DIR}/doc
    DESTINATION share/libpipe
    COMPONENT documentation
    PATTERN "Doxyfile" EXCLUDE)

##############################################################################
## packaging
##############################################################################
## FIXME: make sure that the documentation is compiled and pdfs are 
##        generated prior to packaging!
#
set(CPACK_PACKAGE_NAME "libpipe")
set(CPACK_PACKAGE_VENDOR "massquito.net")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "The pipelining library. Git Commit: "$LIBPIPE_VERSION)

# CPack version strings
SET(CPACK_PACKAGE_VERSION_MAJOR 2)
SET(CPACK_PACKAGE_VERSION_MINOR 1)
SET(CPACK_PACKAGE_VERSION_PATCH 0)

SET(CPACK_RESOURCE_FILE_README "${LIBPIPE_SOURCE_DIR}/README.txt")
SET(CPACK_RESOURCE_FILE_LICENSE "${LIBPIPE_SOURCE_DIR}/LICENSE.txt")

set(CPACK_COMPONENTS_ALL libraries headers documentation examples)
set(CPACK_COMPONENT_LIBRARIES_DISPLAY_NAME "Libraries")
set(CPACK_COMPONENT_HEADERS_DISPLAY_NAME "C++ Development Headers")
set(CPACK_COMPONENT_DOCUMENTATION_DISPLAY_NAME "C++ Interface Documentation")
set(CPACK_COMPONENT_EXAMPLES_DISPLAY_NAME "Compiled Examples")

set(CPACK_COMPONENT_LIBRARIES_DESCRIPTION
    "Compiled libraries.")
set(CPACK_COMPONENT_HEADERS_DESCRIPTION
    "C++ header files for libpipe development.")
set(CPACK_COMPONENT_DOCUMENTATION_DESCRIPTION
    "The C++ libpipe interface documentation (Doxygen).")
set(CPACK_COMPONENT_EXAMPLES_DESCRIPTION
    "Compiled examples.")

INCLUDE(CPack)
