libpipe README
==============

How to install libpipe:

1) Run first cmake:

You have the following options:
ENABLE_TESTING [Default: TRUE]
    compiles the tests 
ENABLE_EXAMPLES [Default: FALSE]
    compile the examples 
ENABLE_COVERAGE [Default: FALSE]
    allows to generate a coverage report 
ENABLE_THREADING [Default: FALSE]
    generate multithreaded libpipe 
CMAKE_INSTALL_PREFIX [Default: /usr/]
    allows to specify the installation path 
CMAKE_BUILD_TYPE
    controls the type of build
        None (CMAKE_C_FLAGS or CMAKE_CXX_FLAGS used)
        Debug (CMAKE_C_FLAGS_DEBUG or CMAKE_CXX_FLAGS_DEBUG)
        Release (CMAKE_C_FLAGS_RELEASE or CMAKE_CXX_FLAGS_RELEASE)
        RelWithDebInfo (CMAKE_C_FLAGS_RELWITHDEBINFO or CMAKE_CXX_FLAGS_RELWITHDEBINFO
        MinSizeRel (CMAKE_C_FLAGS_MINSIZEREL or CMAKE_CXX_FLAGS_MINSIZEREL)


e.g. run cmake like this

cmake path_to_libpipe_src -DENABLE_EXAMPLES=TRUE -DENABLE_COVERAGE=TRUE -DCMAKE_BUILD_TYPE=RelWithDebInfo

2) Run make: 

make

3) To install it run

make install

4) To run the tests run

make test

5) To make coverage run

make test
make coverage