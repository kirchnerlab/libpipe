# require boost
SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD OFF)
FIND_PACKAGE(Boost COMPONENTS program_options system REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
# make sure the examples are debuggable
SET(CMAKE_CXX_FLAGS_DEBUG  "-O0 -Werror -ggdb3 -D_FILE_OFFSET_BITS=64")
# compile and link
ADD_EXECUTABLE(example-uppercase-strings example-uppercase-strings.cpp)
TARGET_LINK_LIBRARIES(example-uppercase-strings pipe)
ADD_EXECUTABLE(example-strings-mtime example-strings-mtime.cpp)
TARGET_LINK_LIBRARIES(example-strings-mtime pipe)
ADD_EXECUTABLE(example-rtc example-rtc.cpp)
TARGET_LINK_LIBRARIES(example-rtc pipe)
INSTALL(TARGETS example-strings-mtime example-uppercase-strings example-rtc
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    COMPONENT examples
)
