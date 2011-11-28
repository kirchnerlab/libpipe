# compile and link
ADD_EXECUTABLE(example-uppercase-strings example-uppercase-strings.cpp)
TARGET_LINK_LIBRARIES(example-uppercase-strings pipe)
ADD_EXECUTABLE(example-strings-mtime example-strings-mtime.cpp)
TARGET_LINK_LIBRARIES(example-strings-mtime pipe)
ADD_EXECUTABLE(example-rtc example-rtc.cpp)
TARGET_LINK_LIBRARIES(example-rtc pipe )
ADD_EXECUTABLE(example-matrices example-matrices.cpp)
TARGET_LINK_LIBRARIES(example-matrices pipe )

INSTALL(TARGETS example-strings-mtime example-uppercase-strings example-rtc
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    COMPONENT examples
)

    
CONFIGURE_FILE(${LIBPIPE_SOURCE_DIR}/examples/inputFileFilterJSON.txt.cmake
    ${LIBPIPE_BINARY_DIR}/examples/inputFileFilterJSON.txt
    @ONLY IMMEDIATE
    )
    
CONFIGURE_FILE(${LIBPIPE_SOURCE_DIR}/examples/inputFilePipelineJSON.txt.cmake
    ${LIBPIPE_BINARY_DIR}/examples/inputFilePipelineJSON.txt
    @ONLY IMMEDIATE
    )        
    
CONFIGURE_FILE(${LIBPIPE_SOURCE_DIR}/examples/inputFileConnectionJSON.txt.cmake
    ${LIBPIPE_BINARY_DIR}/examples/inputFileConnectionJSON.txt
    @ONLY IMMEDIATE
    )
    
CONFIGURE_FILE(${LIBPIPE_SOURCE_DIR}/examples/inputFileParametersJSON.txt.cmake
    ${LIBPIPE_BINARY_DIR}/examples/inputFileParametersJSON.txt
    @ONLY IMMEDIATE
    )  
        
CONFIGURE_FILE(${LIBPIPE_SOURCE_DIR}/examples/inputFileFilterJSONMatrix.txt.cmake
    ${LIBPIPE_BINARY_DIR}/examples/inputFileFilterJSONMatrix.txt
    @ONLY IMMEDIATE
    )
    
CONFIGURE_FILE(${LIBPIPE_SOURCE_DIR}/examples/inputFilePipelineJSONMatrix.txt.cmake
    ${LIBPIPE_BINARY_DIR}/examples/inputFilePipelineJSONMatrix.txt
    @ONLY IMMEDIATE
    )        
    
CONFIGURE_FILE(${LIBPIPE_SOURCE_DIR}/examples/inputFileConnectionJSONMatrix.txt.cmake
    ${LIBPIPE_BINARY_DIR}/examples/inputFileConnectionJSONMatrix.txt
    @ONLY IMMEDIATE
    )    