SET(SRCS 
    ctc/Algorithm.cpp
    ctc/ModificationTimeManager.cpp
    ctc/Filter.cpp
    ctc/Manager.cpp
    ctc/Pipeline.cpp
    utilities/Exception.cpp
    Request.cpp
)

ADD_LIBRARY(pipe ${SRCS})
TARGET_LINK_LIBRARIES(pipe)

INSTALL(TARGETS pipe
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    COMPONENT libraries
)

