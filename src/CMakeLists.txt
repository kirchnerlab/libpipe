
SET(SRCS 
    rtc/ConfigLibconfig.cpp
    rtc/Controler.cpp
    rtc/Pipeline.cpp
    rtc/Loader.cpp
    rtc/Algorithm.cpp
    rtc/Manager.cpp
    rtc/Filter.cpp
    Algorithm.cpp
    Exception.cpp
    Filter.cpp
    Manager.cpp
    Request.cpp
    ModificationTimeManager.cpp
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


