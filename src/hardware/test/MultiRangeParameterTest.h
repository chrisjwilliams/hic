#ifndef MULTIRANGEPARAMETERTEST_H
#define MULTIRANGEPARAMETERTEST_H

#include <cppunit/extensions/HelperMacros.h>

/**
 * @file MultiRangeParameterTest.h
 */

namespace hic {

/**
 * @class MultiRangeParameterTest
 * 
 * @brief
 *    unit test for the MultiRangeParameterTest
 * @details
 * 
 */
class MultiRangeParameterTest : public CppUnit::TestFixture
{
    public:
        CPPUNIT_TEST_SUITE( MultiRangeParameterTest );
        CPPUNIT_TEST( test_stringsInt );
        CPPUNIT_TEST( test_setMinimum );
        CPPUNIT_TEST( test_setMaximum );
        CPPUNIT_TEST_SUITE_END();

    public:
        void setUp();
        void tearDown();

        // Test Methods
        void test_stringsInt();
        void test_setMinimum();
        void test_setMaximum();

    public:
        /// MultiRangeParameterTest constructor.
        MultiRangeParameterTest();

        /// MultiRangeParameterTest destructor.
        ~MultiRangeParameterTest();

    private:
};

} // namespace hic

#endif // MULTIRANGEPARAMETERTEST_H 
