
SET(SRCS 
    rtc/Data.cpp
    rtc/Config.cpp
    rtc/ConfigJSON.cpp
    rtc/Pipeline.cpp
    rtc/PipelineLoader.cpp
    rtc/Algorithm.cpp
    rtc/Manager.cpp
    rtc/Filter.cpp  
    ctc/Algorithm.cpp
    ctc/ModificationTimeManager.cpp
    ctc/Filter.cpp
    ctc/Manager.cpp
    ctc/Pipeline.cpp
    utilities/Exception.cpp
    utilities/Time.cpp
    Request.cpp
)

ADD_LIBRARY(pipe ${SRCS})
TARGET_LINK_LIBRARIES(pipe ${Boost_LIBRARIES})


INSTALL(TARGETS pipe
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    COMPONENT libraries
)


