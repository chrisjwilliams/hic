#ifndef LOFARBEAMTEST_H
#define LOFARBEAMTEST_H

#include <cppunit/extensions/HelperMacros.h>

/**
 * @file LofarBeamTest.h
 */

namespace hic {

/**
 * @class LofarBeamTest
 * 
 * @brief
 *     Unit test for LofarBeam class
 * @details
 * 
 */
class LofarBeamTest : public CppUnit::TestFixture
{
    public:
        CPPUNIT_TEST_SUITE( LofarBeamTest );
        CPPUNIT_TEST( test_frequencySetting );
        CPPUNIT_TEST( test_subbandSetting );
        CPPUNIT_TEST_SUITE_END();

    public:
        void setUp();
        void tearDown();

        // Test Methods
        void test_frequencySetting();
        void test_subbandSetting();

    public:
        /// LofarBeamTest constructor.
        LofarBeamTest();

        /// LofarBeamTest destructor.
        ~LofarBeamTest();

    private:
};

} // namespace hic

#endif // LOFARBEAMTEST_H 
