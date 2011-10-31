libpipe README
==============

How to install libpipe:

1) Run first cmake:

You have the following options:
ENABLE_TESTING Default: TRUE
compiles the tests
ENABLE_EXAMPLES Default: FALSE
compile the examples
ENABLE_COVERAGE Default: FALSE
allows to generate a coverage report

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