#ifndef RANGETEST_H
#define RANGETEST_H

#include <cppunit/extensions/HelperMacros.h>

/**
 * @file RangeTest.h
 */

namespace hic {

/**
 * @class RangeTest
 * 
 * @brief
 *    Unit test for the Range class
 * @details
 * 
 */
class RangeTest : public CppUnit::TestFixture
{
    public:
        CPPUNIT_TEST_SUITE( RangeTest );
        CPPUNIT_TEST( test_strings );
        CPPUNIT_TEST_SUITE_END();

    public:
        void setUp();
        void tearDown();

        // Test Methods
        void test_strings();

    public:
        /// RangeTest constructor.
        RangeTest();

        /// RangeTest destructor.
        ~RangeTest();

    private:
};

} // namespace hic

#endif // RANGETEST_H 
