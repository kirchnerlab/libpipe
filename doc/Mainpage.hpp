/*!

\mainpage libpipe: a lightweight C++ pipelining library

\section sec_intro Introduction

\section sec_install Installation

\section Usage

Usage of Fabrics

 LIBPIPE supports factories for the generation of Algorithm and Managers Objects.
 The Fabrics are defined as \c AlgorithmFactory and \c ManagerFactory
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


\section sec_examples Examples

\section sec_appendix Appendix

\subsection sec_issues Known Issues

*/

