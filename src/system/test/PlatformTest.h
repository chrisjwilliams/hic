#ifndef PLATFORMTEST_H
#define PLATFORMTEST_H

#include <cppunit/extensions/HelperMacros.h>

/**
 * @file PlatformTest.h
 */

namespace hic {

/**
 * @class PlatformTest
 * 
 * @brief
 * 
 * @details
 * 
 */
class PlatformTest : public CppUnit::TestFixture
{
    public:
        CPPUNIT_TEST_SUITE( PlatformTest );
        CPPUNIT_TEST( test_method );
        CPPUNIT_TEST_SUITE_END();

    public:
        void setUp();
        void tearDown();

        // Test Methods
        void test_method();

    public:
        /// PlatformTest constructor.
        PlatformTest();

        /// PlatformTest destructor.
        ~PlatformTest();

    private:
};

} // namespace hic

#endif // PLATFORMTEST_H 
