
SET(SRCS 
    AlgorithmRTC.cpp
    ManagerRTC.cpp
    FilterRTC.cpp
    Algorithm.cpp
    Exception.cpp
    Filter.cpp
    Manager.cpp
    Request.cpp
    ModificationTimeManager.cpp
)

ADD_LIBRARY(pipe ${SRCS})
TARGET_LINK_LIBRARIES(pipe)

INSTALL(TARGETS pipe
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    COMPONENT libraries
)


