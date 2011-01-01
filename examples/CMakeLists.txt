SET(CMAKE_CXX_FLAGS_DEBUG  "-O0 -Werror -ggdb3 -D_FILE_OFFSET_BITS=64")
ADD_EXECUTABLE(example-uppercase-strings example-uppercase-strings.cpp)
TARGET_LINK_LIBRARIES(example-uppercase-strings mstk)
ADD_EXECUTABLE(example-strings-mtime example-strings-mtime.cpp)
TARGET_LINK_LIBRARIES(example-strings-mtime mstk)

