SET(CMAKE_CXX_FLAGS_DEBUG  "-O0 -Werror -ggdb3 -D_FILE_OFFSET_BITS=64")
ADD_EXECUTABLE(testFilters testFilters.cpp)
TARGET_LINK_LIBRARIES(testFilters mstk)

