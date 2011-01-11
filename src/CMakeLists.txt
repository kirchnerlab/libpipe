
SET(SRCS 
    algorithm/Algorithm.cpp
    pipeline/Filter.cpp
    pipeline/Manager.cpp
    pipeline/Request.cpp
    pipeline/SimpleManager.cpp
    pipeline/ModificationTimeManager.cpp
)

ADD_LIBRARY(pipe ${SRCS})
TARGET_LINK_LIBRARIES(pipe)

INSTALL(TARGETS pipe
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
)

