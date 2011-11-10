/*!
\mainpage Libpipe Documentation
\section sec_intro Introduction
\section sec_install Installation
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

\section Usage

<h3> Generate new Runtime Configuration Algorithms </h3>

To generate a new Algorithm you need to generate a new class which inherits from libpipe::rtc::Algorithm.
This class needs to implement the following functions:
<ul>
    <li>public methods:
    <ul>
        <li>\code static Algorithm* create() \endcode</li>
        <li>\code void update(libpipe::Request& req) \endcode</li>
        <li>\code The Destructor \endcode</li>
    </ul></li>
    <li> protected methods:
    <ul>
        <li>\code The Constructor\endcode</li>
    </ul></li>
    <li> private methods and variables:
    <ul>
        <li>\code static const bool registerLoader() \endcode</li>
        <li>\code static const bool registered_;\endcode</li>
    </ul></li>

</ul>
Lets go through the individual functions and what you need to implement:

<h4> create() Method </h4>
This method needs to return a pointer to the base class. Internally the pointer should be a pointer
to your algorithm class. So the implementation should look like this:
\code
        static Algorithm* create()
        {
            return new YOURAlgorithm;
        }
\endcode

<h4> update(libpipe::Request& req) Method </h4>
This method will contain your actual algorithm. In the end the method should return the request.
To add Information to the request trace use the following code inside the method:
\code LIBPIPE_PIPELINE_TRACE(req, "YOUR MESSAGE"); \endcode
To have access to your defined in- and output ports you should add the
following cast at the beginning of the method for convenience:
\code
boost::shared_ptr<libpipe::rtc::SharedData<std::string> > input =
     boost::dynamic_pointer_cast<libpipe::rtc::SharedData<std::string>
     >(this->getPort("YOUR_INPUT_PORT"));
\endcode
This code should cast your port from the libpipe::rtc::data object back to your original data type.
In the example above the input data is of type libpipe::rtc::SharedData<std::string>. After the cast
you can access your input over the variable \c input in your code like you would access a normal pointer.

If you want to delete memory if a delete request is called on your algorithm you can do this by checking
the type of the request:
\code
if (req.is(libpipe::Request::UPDATE) and this->needUpdate()) {
    //code if update is called
} else if (req.is(libpipe::Request::DELETE)) {
    //code if delete is called
}
\endcode

<h4> The Destructor </h4>
If you have not allocated memory in your class an empty destructor is sufficient.

<h4> The Constructor </h4>
Make sure to call the libpipe::rtc::Algorithm Constructor.
\code YOUR_ALGORITHM() :
                libpipe::rtc::Algorithm()
        { ...
\endcode
Inside the constructor register your in- and output ports.
\code
ports_["YOUR_PORT_IDENTIFIER"] = boost::make_shared<
                    libpipe::rtc::SharedData<std::string> >();
\endcode
In the example above you will register the port "YOUR_PORT_IDENTIFIER" with the Type
libpipe::rtc::SharedData<std::string>. If you want to use your own Type look at section
<a href="#datatypes"> Datatype</a>. Your Types need to be encapsulated in boost::shared_ptr.

If you define output Ports make sure to initialize these ports. Otherwise you will get segmentation faults.
\code
ports_["YOUR_OUTPUT_PORT"] = boost::make_shared<
   libpipe::rtc::SharedData<std::string> >(new std::string);
\endcode

<h4> registerLoader() Method </h4>

This method will register your new algorithm class in the AlgorithmFactory.
You can copy paste this method to your algorithm class, only change the identifier
to you own individual one and call the create methode of your own class.
\code
static const bool registerLoader()
{
    std::string ids = "YOUR_ALGORITM_IDENTIFIER";
    return libpipe::rtc::AlgorithmFactory::instance().registerType(ids,YOUR_ALGORITHM::create);
}
\endcode
To register your algorithm you need also to add this line of code outside your class:
\code
const bool YOUR_ALGORITHM::registered_ = registerLoader();
\endcode



<h3> Generate new Managers </h3>

If you really need to, implement the following functions:
<ul>
    <li>public methods:
    <ul>
        <li>\code static Manager* create() \endcode</li>
        <li>\code void processRequest(Request& req);\endcode</li>
        <li>\code The Destructor \endcode</li>
    </ul></li>
    <li> protected methods:
    <ul>
        <li>\code The Constructor\endcode</li>
    </ul></li>
    <li> private methods and variables:
    <ul>
        <li>\code static const bool registerLoader() \endcode</li>
        <li>\code static const bool registered_;\endcode</li>
    </ul></li>
</ul>

Lets go through the individual functions and what you need to implement:

<h4> create() Method </h4>
This method needs to return a pointer to the base class. Internally the pointer should be a pointer
to your manager class. So the implementation should look like this:
\code
        static Manager* create()
        {
            return new YOUR_MANAGER;
        }
\endcode

<h4> processRequest(Request& req) Method </h4>
Process a processing request. In the simple base class implementation
the manager will call the \c process request method of all filters
it depends on and will subsequently execute its own algorithm. If the request is
delete it disconnects from all the algorithm it depends on.


<h4> The Destructor </h4>
If you have not allocated memory in your class an empty destructor is sufficient.

<h4> The Constructor </h4>
Make sure to call the libpipe::rtc::Manager Constructor.
\code YOUR_MANAGER() :
                libpipe::rtc::Manager()
        { ...
\endcode
<h4> registerLoader() Method </h4>

This method will register your new manager class in the ManagerFactory.
You can copy paste this method to your algorithm class, only change the identifier
to you own individual one and call the create methode of your own class.
\code
static const bool registerLoader()
{
    std::string ids = "YOUR_MANAGER_IDENTIFIER";
    return libpipe::rtc::ManagerFactory::instance().registerType(ids,YOUR_MANAGER::create);
}
\endcode
To register your manager you need also to add this line of code outside your class:
\code
const bool YOUR_MANAGER::registered_ = registerLoader();
\endcode

<h3>Usage of Factories</h3>

 LIBPIPE supports factories for the generation of Algorithm and Managers Objects.
 The Factories are defined as \c AlgorithmFactory and \c ManagerFactory
 In order to support the generation of Filter at runtime LIBPIPE provides a factory-based
  (compile time) plugin system:  every algorithm and manager class must provide a create method.
  The nifty thing about the LIBPIPE implementation of this setup is that adding a new class
  does not require editing any existing files. The whole procedure works the following way:
 \li If there is a new class that needs to be supported (e.g. \c IdentityAlgorithm),
     the user writes a class called \c IdentityAlgorithm, which is derived from
     \c libpipe::rtc::Algorithm.
 \li \c IdentityAlgorithm declares and defines its \c create() function, which
     constructs a \c Algorithm.
 \li The startup code of \c IdentityAlgorithm would then register the new Algorithm
     with the \c AlgorithmFactory.
 Overall, the beginning of the implementation file would look like this:
 \code
 // the virtual constructor (static function)
 static Algorithm* IdentityAlgorithm::create() {
    return new IdentityAlgorithm;
 }
 const bool IdentityAlgorithm::registerLoader()
 {
     return AlgorithmFactory::instance().registerType("IdentityAlgorithm",
         IdentityAlgorithm::create);
 }

 // startup code to register the loader with the search result loader factory.
 const bool IdentityAlgorithm::registered_ = registerLoader();
 \endcode

 In summary, every new Algorithm or Manager will notify the factory of its identifier
 and pass along a virtual constructor for the respective loader class.

<h3> <a name="datatypes">Generate new Datatypes </a></h3>
If you want to create your own data type you need to inherit from libpipe::rtc::Data .
If you want to use your data type in multithreaded libpipe, you also need to implement your
datatype thread safe.

<h3> Input Files </h3>


\section sec_examples Examples

\section sec_appendix Appendix

\subsection sec_issues Known Issues

*/

