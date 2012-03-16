/**
\page usage Usage

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
following macro at the beginning of the method for convenience:
\code
LIBPIPE_PREPARE_READ_ACCESS(input1_, tempIn1, Doubles, "MatrixIn1");
LIBPIPE_PREPARE_WRITE_ACCESS(output_, tempOut, Doubles, "MatrixOut");
\endcode
This macro gives you access to your in and output. If you want to write your data make sure that you
call \cLIBPIPE_PREPARE_WRITE_ACCESS, as this enables thread safe writting under the hood.

The first argument of your macro will generate a variable of this name where your in/output is stored.
The second parameter will give you a variable with direct access to the data. The third parameter
will be the type of your data. The last argument is the name of the port where your data is stored.

If you want to delete memory if a delete request is called on your algorithm you can do this by checking
the type of the request:
\code
if (req.is(libpipe::Request::UPDATE) and this->needUpdate()) {
    //code if update is called
} else if (req.is(libpipe::Request::DELETE)) {
    //code if delete is called
}
\endcode

At the end of you update methode you need to clean up your data objects. This can be done by the
macro \cLIBPIPE_CLEAN_ACCESS(input1_) where the first argument is your variable storing the
in/output is stored.


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
You can use the provided libpipe::rtc::SharedData template class to add your own datatypes.
If you want to use std::vector to share data between filters you can do this the following way.
\code
libpipe::rtc::SharedData<std::vector<double> >
\endcode
If you use multithreading in your pipeline, the SharedData class also provides fast thread safe access.
However you need to lock the class before you make use of any member functions. For multithreading
sharedData provides the following functions:
\code
libpipe::rtc::SharedData<T>::lock()
libpipe::rtc::SharedData<T>::shared_lock()
libpipe::rtc::SharedData<T>::unlock()
\endcode
Before calling any member functions you need to lock the class. With \c lock() you get unique access
to the class, you need this if you want to call \c set(...). With \c shared_lock() you get shared access
to the class, this is needed if you want to call \c get() or \c isNull().
When you are finished with the access make sure to call \c unlock(). Otherwise you might get
a dead lock.

If you want to create your own data type you need to inherit from libpipe::rtc::Data .
If you want to use your data type in multithreaded libpipe, you also need to implement your
datatype thread safe.


<h3> Implementation of own Input Files types</h3>

With the libpipe library JSON input files are supported. You can define your own input files
by implementing a own class which inherits from libpipe::rtc::Config. For details see our implementation
in libpipe::rtc::ConfigJSON. To make use of your own class you need to change one line in
libpipe::rtc::PipelineLoader:
\code
...
PipelineLoader::PipelineLoader(const std::map<std::string, std::string>& inputFile)
{
    //change this line with your own Implementation to support other input files.
    configuration_ = new ConfigJSON;
    ...
\endcode

<h3> JSON Input Files</h3>

To configure libpipe with JSON files you need to generate three different files.

<dl>
<dt>
Filter
</dt>
<dd>defines your filters</dd>
<dt>
Connection
</dt>
<dd>defines the connections between your filters</dd>
<dt>
Pipeline
</dt>
<dd>defines execution of your pipeline</dd>
<dt>
Parameters
</dt>
<dd>defines parameters for your filter objects</dd>
</dl>


<h4>Filter file</h4>
In this file you need to define all filters. One Filter object will look like this:
\code
{
    "filters": [
    ...
    ,{
            "filterIdentifier": "IDENTIFIER_OF_FILTER",
            "algorithmName": "NAME_OF_ALGORITHM",
            "managerName": "NAME_OF_MANAGER"
    }...
    ]
}
\endcode
\c filterIdentifier is your own chosen Identifier for the filter defined. \c algorithmName is the name of
the algorithm class you want to use. \c managerName is the name of the manager class you want to use.

<h4>Connections file</h4>
In this file you define the connections between the individual filters.

\code
{
    "connections": [
        ...
        ,{
            "filterName": "IDENTIFIER_OF_FILTER",
            "identifier": "IDENTIFIER_OF_THIS",
            "precursors": [
                {
                    "precursorName": "IDENTIFIER_OF_PRECURSOR"
                }
            ],
            "ports": [
                {
                    "filterName": "IDENTIFIER_OF_PRECURSOR",
                    "portNameOfFilter": "PORT_IDENTIFIER_OF_PRECURSOR",
                    "portNameOfThis": "PORT_IDENTIFIER_OF_THIS"
                }
            ]
        }
        ...
    ]
}
\endcode
\c filterName is an identifier used to define a filter. \c identifier identifies this filter object.
\c precursorName identifies the precursor filter object. \c ports::filterName identifies the precursor
filter object. \c portNameOfFilter defines the port of this filter which will be connected to
\c portNameOfThis port of the precursor filter object.

<h4>Pipeline file</h4>
Here the execution of your filters is defined.
\code
{
    "pipeline": [
        ...
        ,{
            "filterName": "IDENTIFIER_OF_FILTER",
            "requestType": "UPDATE",
            "requestRank": 1,
            "makeTrace": "true"
        }
        ...
    ]
}
\endcode
\c filterName identifies the filter object where the in \c requestType defined request is executed.
At the moment only the UPDATE and DELETE request can be executed. \c requestRank is an integer
defining the order of execution the higher the later it will be executed. With the boolean \c makeTrace
one can define if you want to generate a trace of the execution of this object.

<h4>Parameters file</h4>
In this file parameters for Filter Objects are defined.
\code
{
    "parameters": [
        {
            "filterIdentifier": "Source",
            "parameters": [
                {
                    "paramIdentifier": "SourceString",
                    "param": "Hello how are you World?"
                }
             ]
        },
        ...
    ]
}
\endcode
\c filterIdentifier identifies the filter object where a new parameter \c SourceString with value \param
is defined. To access a parameter from the object the following code can be used. Where the template
parameter is the type of the parameter.
\code
parameters_.get<double>("ParameterName");
\endcode


*/
