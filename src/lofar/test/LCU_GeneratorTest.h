#ifndef LCU_GENERATORTEST_H
#define LCU_GENERATORTEST_H

#include <cppunit/extensions/HelperMacros.h>

/**
 * @file LCU_GeneratorTest.h
 */

namespace hic {

/**
 * @class LCU_GeneratorTest
 * 
 * @brief
 *   unit test for the LCU_Generator
 * @details
 * 
 */
class LCU_GeneratorTest : public CppUnit::TestFixture
{
    public:
        CPPUNIT_TEST_SUITE( LCU_GeneratorTest );
        CPPUNIT_TEST( test_method );
        CPPUNIT_TEST_SUITE_END();

    public:
        void setUp();
        void tearDown();

        // Test Methods
        void test_method();

    public:
        /// LCU_GeneratorTest constructor.
        LCU_GeneratorTest();

        /// LCU_GeneratorTest destructor.
        ~LCU_GeneratorTest();

    private:
};

} // namespace hic

#endif // LCU_GENERATORTEST_H 
