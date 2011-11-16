#
# configure/build libpipe tests
#
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
        ${Boost_LIBRARIES}
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
ENDMACRO(ADD_LIBPIPE_TEST name exe src)


# include directories
INCLUDE_DIRECTORIES(
    ${LIBPIPE_SOURCE_DIR}/test/include
    ${LIBPIPE_SOURCE_DIR}/include
    ${LIBPIPE_BINARY_DIR}/include
    ${LIBPIPE_BINARY_DIR}/test/include
    ${CMAKE_CURRENT_SOURCE_DIR}   
)


#### Sources
SET(SRCS_UTILITIES_TIME utilities/Time-test.cpp)
SET(SRCS_RTC_PIPELINE rtc/Pipeline-test.cpp)
SET(SRCS_PIPELINE_LOADER rtc/PipelineLoader-test.cpp)
SET(SRCS_CONFIGJSON rtc/ConfigJSON-test.cpp)
SET(SRCS_CONFIG rtc/Config-test.cpp)
SET(SRCS_MANAGERRTC rtc/Manager-test.cpp)
SET(SRCS_ALGORITHMRTC rtc/Algorithm-test.cpp)
SET(SRCS_FILTERRTC rtc/Filter-test.cpp)
SET(SRCS_RTC_SHAREDDATA rtc/SharedData-test.cpp)
SET(SRCS_FACTORY utilities/Factory-test.cpp)
SET(SRCS_SINGLETON utilities/Singleton-test.cpp)
SET(SRCS_EXCEPTION utilities/Exception-test.cpp)
SET(SRCS_PIPELINE ctc/Pipeline-test.cpp)
SET(SRCS_SHAREDDATA ctc/SharedData-test.cpp)
SET(SRCS_MODIFICATIONTIMEMANAGER ctc/ModificationTimeManager-test.cpp)
SET(SRCS_MANAGER ctc/Manager-test.cpp)
SET(SRCS_FILTER ctc/Filter-test.cpp)
SET(SRCS_BASICFILTER ctc/BasicFilter-test.cpp)
SET(SRCS_ALGORITHM ctc/Algorithm-test.cpp)
SET(SRCS_REQUESTEXCEPTION RequestException-test.cpp)
SET(SRCS_REQUEST Request-test.cpp)

#### Tests
ADD_LIBPIPE_TEST("utilities/Time" test_utilities_time ${SRCS_UTILITIES_TIME})
ADD_LIBPIPE_TEST("rtc/Pipeline" test_rtc_pipeline ${SRCS_RTC_PIPELINE})
ADD_LIBPIPE_TEST("rtc/PipelineLoader" test_rtc_pipelineLoader ${SRCS_PIPELINE_LOADER})
ADD_LIBPIPE_TEST("rtc/ConfigJSON" test_rtc_configJSON ${SRCS_CONFIGJSON})
ADD_LIBPIPE_TEST("rtc/Config" test_rtc_config ${SRCS_CONFIG})
ADD_LIBPIPE_TEST("rtc/Manager" test_managerrtc ${SRCS_MANAGERRTC})
ADD_LIBPIPE_TEST("rtc/Algorithm" test_algorithmrtc ${SRCS_ALGORITHMRTC})
ADD_LIBPIPE_TEST("rtc/Filter" test_filterrtc ${SRCS_FILTERRTC})
ADD_LIBPIPE_TEST("utilities/Factory" test_factory ${SRCS_FACTORY})
ADD_LIBPIPE_TEST("utilities/Singleton" test_singleton ${SRCS_SINGLETON})
ADD_LIBPIPE_TEST("rtc/SharedData" test_rtc_shareddata ${SRCS_RTC_SHAREDDATA})
ADD_LIBPIPE_TEST("Pipeline" test_pipeline ${SRCS_PIPELINE})
ADD_LIBPIPE_TEST("RequestException" test_requestexception ${SRCS_REQUESTEXCEPTION})
ADD_LIBPIPE_TEST("Request" test_request ${SRCS_REQUEST})
ADD_LIBPIPE_TEST("ModificationTimeManager" test_modificationtimemanager ${SRCS_MODIFICATIONTIMEMANAGER})
ADD_LIBPIPE_TEST("Manager" test_manager ${SRCS_MANAGER})
ADD_LIBPIPE_TEST("Filter" test_filter ${SRCS_FILTER})
ADD_LIBPIPE_TEST("BasicFilter" test_basicfilter ${SRCS_BASICFILTER})
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



CONFIGURE_FILE(${LIBPIPE_SOURCE_DIR}/test/rtc/wrongInputFile.txt.cmake
    ${LIBPIPE_BINARY_DIR}/test/wrongInputFile.txt
    @ONLY IMMEDIATE
)

CONFIGURE_FILE(${LIBPIPE_SOURCE_DIR}/test/rtc/inputFileFilterJSON.txt.cmake
    ${LIBPIPE_BINARY_DIR}/test/inputFileFilterJSON.txt
    @ONLY IMMEDIATE
)

CONFIGURE_FILE(${LIBPIPE_SOURCE_DIR}/test/rtc/inputFileConnectionJSON.txt.cmake
    ${LIBPIPE_BINARY_DIR}/test/inputFileConnectionJSON.txt
    @ONLY IMMEDIATE
)

CONFIGURE_FILE(${LIBPIPE_SOURCE_DIR}/test/rtc/inputFilePipelineJSON.txt.cmake
    ${LIBPIPE_BINARY_DIR}/test/inputFilePipelineJSON.txt
    @ONLY IMMEDIATE
)
