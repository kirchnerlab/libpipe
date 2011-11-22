/**
\page installation Installation

\subsection Release

<ol>
<li> Run cmake:

You have the following options:
<dl>
<dt>
ENABLE_TESTING [Default: TRUE]
</dt>
<dd>compiles the tests</dd>
<dt>
ENABLE_EXAMPLES [Default: FALSE]
</dt>
<dd>compile the examples</dd>
<dt>
ENABLE_COVERAGE [Default: FALSE]
</dt>
<dd>allows to generate a coverage report</dd>
<dt>
<dt>
ENABLE_THREADING [Default: FALSE]
</dt>
<dd>generate multithreaded libpipe</dd>
<dt>
CMAKE_INSTALL_PREFIX [Default: /usr/local]
</dt>
<dd>allows to specify the installation path</dd>
<dt>
CMAKE_BUILD_TYPE
</dt>
<dd>controls the type of build
<ul><li>None (CMAKE_C_FLAGS or CMAKE_CXX_FLAGS used)
</li><li>Debug (CMAKE_C_FLAGS_DEBUG or CMAKE_CXX_FLAGS_DEBUG)
</li><li>Release (CMAKE_C_FLAGS_RELEASE or CMAKE_CXX_FLAGS_RELEASE)
</li><li>RelWithDebInfo (CMAKE_C_FLAGS_RELWITHDEBINFO or CMAKE_CXX_FLAGS_RELWITHDEBINFO
</li><li>MinSizeRel (CMAKE_C_FLAGS_MINSIZEREL or CMAKE_CXX_FLAGS_MINSIZEREL)
</li></ul>
</dd>
</dl>

e.g. run cmake like this

\code cmake path_to_libpipe_src -DENABLE_EXAMPLES=TRUE -DENABLE_COVERAGE=TRUE -DCMAKE_BUILD_TYPE=Debug \endcode
</li>
<li> To compile the project run:

\code make \endcode
</li>
<li> To install libpipe run:

\code make install \endcode
</li>
</ol>
\subsection Distribution
<ol>
<li> To generate installers for libpipe run:
\code
cmake path_to_libpipe_src -DENABLE_EXAMPLES=TRUE -DENABLE_COVERAGE=FALSE -DCMAKE_BUILD_TYPE=Release
make doc && make package
\endcode
</li>
</ol>
\subsection Testing
For testing you can run the included test and measure the coverage of the tests.
<ol>
<li> Call cmake with ENABLE_TESTING true. If you want a coverage report also set ENABLE_COVERAGE to true and make a debug build.
\code \code cmake path_to_libpipe_src -DENABLE_COVERAGE=TRUE -DENABLE_TESTING=TRUE -DCMAKE_BUILD_TYPE=Debug \endcode
</li>
<li> To execute the tests run:

\code make test \endcode
</li>
<li> To generate the coverage report run:
\code make coverage \endcode
</li>
</ol>

*/
