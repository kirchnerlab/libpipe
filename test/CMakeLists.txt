#
# configure/build libpipe tests
#

IF(UNIX)
    SET(LIBCONFIG_PATH libconfig) 
ENDIF(UNIX)
IF(APPLE)
    SET(LIBCONFIG_PATH libconfig/libconfig-1.4.8)    
ENDIF(APPLE)


##############################################################################
# check if have valgrind
##############################################################################
SET(HAVE_VALGRIND TRUE)
FIND_PROGRAM(VALGRIND_EXECUTABLE valgrind)
IF(VALGRIND_EXECUTABLE STREQUAL "VALGRIND_EXECUTABLE-NOTFOUND")
    MESSAGE(STATUS "WARNING: Could not find valgrind. Will NOT build memory tests.")
    SET(HAVE_VALGRIND FALSE)
ENDIF(VALGRIND_EXECUTABLE STREQUAL "VALGRIND_EXECUTABLE-NOTFOUND")

##############################################################################
# macro definitions
##############################################################################
MACRO(ADD_LIBPIPE_TEST name exe src)
    STRING(REGEX REPLACE "test_([^ ]+).*" "\\1" test "${exe}" )
    # build the test
    ADD_EXECUTABLE(${exe} ${src})
    
    SET(TEST_LIBS  
        pipe
        -lconfig++
    )
    
    
    TARGET_LINK_LIBRARIES(${exe} ${TEST_LIBS})
    # add test to global list of unit test
    ADD_TEST(${name} ${exe})
    MESSAGE(STATUS "Adding test for ${name}: ${exe}.")
    # add target for the test
    STRING(REGEX REPLACE "test_([^ ]+).*" "unit_\\1" unittest_target "${exe}" )
    ADD_CUSTOM_TARGET(${unittest_target} COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${exe})
    IF (HAVE_VALGRIND) 
        #add memory test using valgrind
        STRING(REGEX REPLACE "test_([^ ]+).*" "mem_\\1" memtest_name "${exe}" )
        LIST(APPEND memtest_names ${memtest_name})
        LIST(APPEND exe_names ${exe})
        #Add target for the memory test
        ADD_CUSTOM_TARGET(${memtest_name} COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/memcheck.py ${CMAKE_CURRENT_BINARY_DIR}/${exe})
    ENDIF (HAVE_VALGRIND) 
    #Add target for the gcov coverage report for this test
    IF(ENABLE_COVERAGE)
        STRING(REGEX REPLACE "test_([^ ]+).*" "gcov_\\1" gcov_target "${exe}" )
        ADD_CUSTOM_TARGET(${gcov_target} COMMAND /bin/bash ${LIBPIPE_BINARY_DIR}/scripts/for_cmake/unit_coverage.sh ${test})
    ENDIF(ENABLE_COVERAGE)
ENDMACRO(ADD_LIBPIPE_TEST name exe src)


# include directories
INCLUDE_DIRECTORIES(
    ${LIBPIPE_SOURCE_DIR}/test/include
    ${LIBPIPE_SOURCE_DIR}/include
    ${LIBPIPE_BINARY_DIR}/include
    ${LIBPIPE_BINARY_DIR}/test/include
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${LIBPIPE_BINARY_DIR}/lib/${LIBCONFIG_PATH}/include
    
)

LINK_DIRECTORIES(
    ${LIBPIPE_BINARY_DIR}/lib/${LIBCONFIG_PATH}/lib
)

#### Sources
SET(SRCS_LIBPIPEPIPELINE rtc/LibpipePipeline-test.cpp)
SET(SRCS_LIBPIPECREATOR rtc/LibpipeCreator-test.cpp)
SET(SRCS_LIBPIPECONFIGLIBCONFIG rtc/LibpipeConfigLibconfig-test.cpp)
SET(SRCS_LIBPIPECONFIG rtc/LibpipeConfig-test.cpp)
SET(SRCS_MANAGERRTC rtc/Manager-test.cpp)
SET(SRCS_ALGORITHMRTC rtc/Algorithm-test.cpp)
SET(SRCS_FILTERRTC rtc/Filter-test.cpp)
SET(SRCS_OBJECTFACTORY utilities/Factory-test.cpp)
SET(SRCS_SINGLETON utilities/Singleton-test.cpp)
SET(SRCS_SHAREDDATA rtc/SharedData-test.cpp)
SET(SRCS_REQUESTEXCEPTION RequestException-test.cpp)
SET(SRCS_REQUEST Request-test.cpp)
SET(SRCS_MODIFICATIONTIMEMANAGER ModificationTimeManager-test.cpp)
SET(SRCS_MANAGER Manager-test.cpp)
SET(SRCS_FILTER Filter-test.cpp)
SET(SRCS_BASICFILTER BasicFilter-test.cpp)
SET(SRCS_LOG Log-test.cpp)
SET(SRCS_EXCEPTION Exception-test.cpp)
SET(SRCS_ALGORITHM Algorithm-test.cpp)

SET(TEST_LIBS pipe)
IF (ENABLE_COVERAGE)
    SET(TEST_LIBS ${TEST_LIBS} gcov)
ENDIF(ENABLE_COVERAGE)
#### Tests
ADD_LIBPIPE_TEST("rtc/LibpipePipeline" test_libpipepipeline ${SRCS_LIBPIPEPIPELINE})
ADD_LIBPIPE_TEST("rtc/LibpipeCreator" test_libpipecreator ${SRCS_LIBPIPECREATOR})
ADD_LIBPIPE_TEST("rtc/LibpipeConfigLibconfig" test_libpipeconfiglibconfig ${SRCS_LIBPIPECONFIGLIBCONFIG})
ADD_LIBPIPE_TEST("rtc/LibpipeConfig" test_libpipeconfig ${SRCS_LIBPIPECONFIG})
ADD_LIBPIPE_TEST("rtc/Manager" test_managerrtc ${SRCS_MANAGERRTC})
ADD_LIBPIPE_TEST("rtc/Algorithm" test_algorithmrtc ${SRCS_ALGORITHMRTC})
ADD_LIBPIPE_TEST("rtc/Filter" test_filterrtc ${SRCS_FILTERRTC})
ADD_LIBPIPE_TEST("utilities/Factory" test_factory ${SRCS_OBJECTFACTORY})
ADD_LIBPIPE_TEST("utilities/Singleton" test_singleton ${SRCS_SINGLETON})
ADD_LIBPIPE_TEST("rtc/SharedData" test_shareddata ${SRCS_SHAREDDATA})
ADD_LIBPIPE_TEST("RequestException" test_requestexception ${SRCS_REQUESTEXCEPTION})
ADD_LIBPIPE_TEST("Request" test_request ${SRCS_REQUEST})
ADD_LIBPIPE_TEST("ModificationTimeManager" test_modificationtimemanager ${SRCS_MODIFICATIONTIMEMANAGER})
ADD_LIBPIPE_TEST("Manager" test_manager ${SRCS_MANAGER})
ADD_LIBPIPE_TEST("Filter" test_filter ${SRCS_FILTER})
ADD_LIBPIPE_TEST("BasicFilter" test_basicfilter ${SRCS_BASICFILTER})
ADD_LIBPIPE_TEST("Log" test_log ${SRCS_LOG})
ADD_LIBPIPE_TEST("Exception" test_exception ${SRCS_EXCEPTION})
ADD_LIBPIPE_TEST("Algorithm" test_algorithm ${SRCS_ALGORITHM})



LIST(LENGTH memtest_names numtests)
IF(numtests GREATER 0)
    MATH(EXPR numtests ${numtests}-1)
    FOREACH(i RANGE 0 ${numtests})
        LIST(GET memtest_names ${i} memtest_name)
        LIST(GET exe_names ${i} exe)
        MESSAGE(STATUS "Adding memory test for ${memtest_name}: ${exe}.")
        ADD_TEST(${memtest_name}
            ${CMAKE_CURRENT_SOURCE_DIR}/memtest.py ${CMAKE_CURRENT_BINARY_DIR}/${exe} ${CMAKE_BINARY_DIR})
    ENDFOREACH(i RANGE 0 ${numtests}-1)
ENDIF(numtests GREATER 0)


CONFIGURE_FILE(${LIBPIPE_SOURCE_DIR}/test/rtc/inputFile.txt.cmake
    ${LIBPIPE_BINARY_DIR}/test/inputFile.txt
    @ONLY IMMEDIATE
)

CONFIGURE_FILE(${LIBPIPE_SOURCE_DIR}/test/rtc/wrongInputFile.txt.cmake
    ${LIBPIPE_BINARY_DIR}/test/wrongInputFile.txt
    @ONLY IMMEDIATE
)

