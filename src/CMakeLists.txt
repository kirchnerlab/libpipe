
SET(SRCS 
    algorithm/Algorithm.cpp
    pipeline/Filter.cpp
    pipeline/Manager.cpp
    pipeline/Request.cpp
    pipeline/SimpleManager.cpp
    pipeline/ModificationTimeManager.cpp
)

ADD_LIBRARY(mstk ${SRCS})
#TARGET_LINK_LIBRARIES(mstk)

INSTALL(TARGETS mstk
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
)

