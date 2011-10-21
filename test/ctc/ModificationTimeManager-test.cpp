/*
*
* Copyright (c) 2011 David-Matthias Sichau
* Copyright (c) 2011 Marc Kirchner
*
* This file is part of libpipe.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

#include <iostream>
#include <vector>
#include <string>
#include "vigra/unittest.hxx"

#include <libpipe/ctc/Algorithm.hpp>
#include <libpipe/ctc/BasicFilter.hpp>
#include <libpipe/Request.hpp>
#include <libpipe/RequestException.hpp>
#include <libpipe/ctc/ModificationTimeManager.hpp>

#include "ctc/utils.hpp"

using namespace libpipe::ctc;

/** Test suitre for the ModificationTime
 */
struct ModificationTimeManagerTestSuite : vigra::test_suite
{
    /** Constructor.
     * The ModificationTimeManagerTestSuite constructor adds all ModificationTimeManager tests to
     * the test suite. If you write an additional test, add the test
     * case here.
     */
    ModificationTimeManagerTestSuite() :
        vigra::test_suite("ModificationTimeManager")
    {
        add(testCase(&ModificationTimeManagerTestSuite::testProcessRequest));
        add(testCase(&ModificationTimeManagerTestSuite::testUpdateUponOutdate));
    }

    /** Test the request processing.
     */
    void testProcessRequest()
    {
        ModificationTimeManager mtm;
        // no algorithm defined, needs to throw an exception
        libpipe::Request req(libpipe::Request::UPDATE);
        bool thrown = false;
        try {
            req = mtm.processRequest(req);
        } catch (libpipe::RequestException& e) {
            thrown = true;
        }
        shouldEqual(thrown, true);
        // use of needUpdate: add an Algorithm which throws an exception upon
        // execution, don't add any sources and manually set the algorithms
        // mTime to something that is not equal to Algorithm::MAX_TIME. In that
        // case the Manager should NOT execute the algorithm. If it does we can
        // detect this by catching the exception.
        RaiseExceptionAlg* a = new RaiseExceptionAlg();
        a->updateMTime();
        mtm.setAlgorithm(a);
        thrown = false;
        try {
            req = mtm.processRequest(req);
        } catch (libpipe::RequestException& e) {
            thrown = true;
        }
        shouldEqual(thrown, false);
        // now require the update via Algorithm::MAX_TIME
        a->setMTime(Algorithm::MAX_TIME);
        thrown = false;
        try {
            req = mtm.processRequest(req);
        } catch (libpipe::RequestException& e) {
            // only catching the RequestException also ensures that exceptions
            // are encapsulated (RaiseExceptionAlg throws a std::exception)
            thrown = true;
        }
        shouldEqual(thrown, true);
        mtm.setAlgorithm(0);
        delete a;
    }

    /** Require the update via a source with a newer modification time.
     */
    void testUpdateUponOutdate()
    {
        typedef BasicFilter<RaiseExceptionAlg, ModificationTimeManager>
                RaiseFilter;
        typedef BasicFilter<Inc, ModificationTimeManager> IncFilter;

        boost::shared_ptr<IncFilter> i1 (new IncFilter("I1"));
        boost::shared_ptr<IncFilter> i2 (new IncFilter("I2"));

        // connect

        i2->getAlgorithm()->setInput(i1->getAlgorithm()->getOutput());
        i2->getManager()->connect(boost::dynamic_pointer_cast<Filter> (i1));
        int* src = new int(42);
        i1->getAlgorithm()->setInput(src);
        // the following line simulates source behavior for i1
        i1->getAlgorithm()->setMTime(Algorithm::MAX_TIME);
        shouldEqual(*(i1->getAlgorithm()->getOutput()), 0);
        shouldEqual(*(i2->getAlgorithm()->getOutput()), 0);
        libpipe::Request req(libpipe::Request::UPDATE);
        req.setTraceFlag(true);
        req = i2->processRequest(req);
        /*         typedef std::vector<std::string> VS;
         *         VS trace;
         *         req.getTrace(trace);
         *         typedef VS::iterator IT;
         *         for (IT i = trace.begin(); i != trace.end(); ++i) {
         *             std::cerr << *i << '\n';
         *         }
         *         std::cerr << std::flush;
         */

        shouldEqual(*(i1->getAlgorithm()->getOutput()), 43);
        shouldEqual(*(i2->getAlgorithm()->getOutput()), 44);

        // if we re-run, nothing should happen because the source (i1) has
        // an mTime different from Algorithm::MAX_TIME and the dependent
        // algorithm (i2) has an mTime that is younger than the source.
        req.clearTrace();
        req = i2->processRequest(req);
        shouldEqual(*(i1->getAlgorithm()->getOutput()), 43);
        shouldEqual(*(i2->getAlgorithm()->getOutput()), 44);

        // ok, now update the mTime on i1 (and also change the value to be able
        // to observe the change). This should trigger a recalculation of i2
        // ONLY, which we check by abusing the pointer returned by getOutput()
        // to actually change the value 
        *src = 1335;
        i1->getAlgorithm()->updateMTime();
        *(i1->getAlgorithm()->getOutput()) = 110;
        req.clearTrace();
        req = i2->processRequest(req);
        shouldEqual(*(i1->getAlgorithm()->getOutput()), 110);
        shouldEqual(*(i2->getAlgorithm()->getOutput()), 111);

        // close the circle: fake a source update
        i1->getAlgorithm()->setMTime(Algorithm::MAX_TIME);
        req.clearTrace();
        req = i2->processRequest(req);
        shouldEqual(*(i1->getAlgorithm()->getOutput()), 1336);
        shouldEqual(*(i2->getAlgorithm()->getOutput()), 1337);

        delete src;
    }

};

/** The main function that runs the tests for class ModificationTimeManager.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    ModificationTimeManagerTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

