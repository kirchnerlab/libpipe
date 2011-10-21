
SET(SRCS 
    rtc/Data.cpp
    rtc/Config.cpp
    rtc/ConfigLibconfig.cpp
    rtc/Controler.cpp
    rtc/Pipeline.cpp
    rtc/Loader.cpp
    rtc/Algorithm.cpp
    rtc/Manager.cpp
    rtc/Filter.cpp  
    ctc/Algorithm.cpp
    ctc/ModificationTimeManager.cpp
    ctc/Filter.cpp
    ctc/Manager.cpp
    ctc/Pipeline.cpp
    utilities/Exception.cpp
    Request.cpp
)

ADD_LIBRARY(pipe ${SRCS})
ADD_DEPENDENCIES(pipe libconfig)
TARGET_LINK_LIBRARIES(pipe config)


INSTALL(TARGETS pipe
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    COMPONENT libraries
)


