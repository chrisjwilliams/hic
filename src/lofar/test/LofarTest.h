#ifndef LOFARTEST_H
#define LOFARTEST_H

#include <cppunit/extensions/HelperMacros.h>

/**
 * @file LofarTest.h
 */

namespace hic {

/**
 * @class LofarTest
 * 
 * @brief
 * 
 * @details
 * 
 */
class LofarTest : public CppUnit::TestFixture
{
    public:
        CPPUNIT_TEST_SUITE( LofarTest );
        CPPUNIT_TEST( test_subbandWidth );
        CPPUNIT_TEST( test_subband );
        CPPUNIT_TEST( test_ranges );
        CPPUNIT_TEST_SUITE_END();

    public:
        void setUp();
        void tearDown();

        // Test Methods
        void test_subbandWidth();
        void test_subband();
        void test_ranges();

    public:
        /// LofarTest constructor.
        LofarTest();

        /// LofarTest destructor.
        ~LofarTest();

    private:
};

} // namespace hic

#endif // LOFARTEST_H 
