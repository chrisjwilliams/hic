#ifndef STATECONTROLLERTEST_H
#define STATECONTROLLERTEST_H

#include <cppunit/extensions/HelperMacros.h>

/**
 * @file StateControllerTest.h
 */

namespace hic {

/**
 * @class StateControllerTest
 * 
 * @brief
 * 
 * @details
 * 
 */
class StateControllerTest : public CppUnit::TestFixture
{
    public:
        CPPUNIT_TEST_SUITE( StateControllerTest );
        CPPUNIT_TEST( test_method );
        CPPUNIT_TEST_SUITE_END();

    public:
        void setUp();
        void tearDown();

        // Test Methods
        void test_method();

    public:
        /// StateControllerTest constructor.
        StateControllerTest();

        /// StateControllerTest destructor.
        ~StateControllerTest();

    private:
};

} // namespace hic

#endif // STATECONTROLLERTEST_H 
