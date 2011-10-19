
SET(SRCS 
    rtc/LibpipeConfigLibconfig.cpp
    rtc/LibpipeCreator.cpp
    rtc/LibpipePipeline.cpp
    rtc/LibpipeLoader.cpp
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


