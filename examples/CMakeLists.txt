

LINK_DIRECTORIES(
                    ${LIBPIPE_BINARY_DIR}/lib/${LIBCONFIG_PATH}/lib
                 )

# make sure the examples are debuggable
SET(CMAKE_CXX_FLAGS_DEBUG  "-O0 -Werror -ggdb3 -D_FILE_OFFSET_BITS=64")
# compile and link
ADD_EXECUTABLE(example-uppercase-strings example-uppercase-strings.cpp)
TARGET_LINK_LIBRARIES(example-uppercase-strings pipe)
ADD_EXECUTABLE(example-strings-mtime example-strings-mtime.cpp)
TARGET_LINK_LIBRARIES(example-strings-mtime pipe)
ADD_EXECUTABLE(example-rtc example-rtc.cpp)
TARGET_LINK_LIBRARIES(example-rtc pipe -lconfig++)

INSTALL(TARGETS example-strings-mtime example-uppercase-strings example-rtc
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    COMPONENT examples
)


CONFIGURE_FILE(${LIBPIPE_SOURCE_DIR}/examples/inputFile.txt.cmake
    ${LIBPIPE_BINARY_DIR}/examples/inputFile.txt
    @ONLY IMMEDIATE
    )

    
CONFIGURE_FILE(${LIBPIPE_SOURCE_DIR}/examples/inputFileFilter.txt.cmake
    ${LIBPIPE_BINARY_DIR}/examples/inputFileFilter.txt
    @ONLY IMMEDIATE
    )