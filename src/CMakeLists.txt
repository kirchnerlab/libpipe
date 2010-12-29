
SET(SRCS 
    Algorithm.cpp
    Filter.cpp
    FilterData.cpp
    Manager.cpp
    PortInformation.cpp
)

ADD_LIBRARY(mstk ${SRCS})
#TARGET_LINK_LIBRARIES(mstk)

INSTALL(TARGETS mstk
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
)

