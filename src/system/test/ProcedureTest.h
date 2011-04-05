#ifndef PROCEDURETEST_H
#define PROCEDURETEST_H

#include <cppunit/extensions/HelperMacros.h>

/**
 * @file ProcedureTest.h
 */

namespace hic {

/**
 * @class ProcedureTest
 * 
 * @brief
 *   unit test for the Procedure class
 * @details
 * 
 */
class ProcedureTest : public CppUnit::TestFixture
{
    public:
        CPPUNIT_TEST_SUITE( ProcedureTest );
        CPPUNIT_TEST( test_empty );
        CPPUNIT_TEST( test_appendProcedure );
        CPPUNIT_TEST_SUITE_END();

    public:
        void setUp();
        void tearDown();

        // Test Methods
        void test_empty();
        void test_appendProcedure();

    public:
        /// ProcedureTest constructor.
        ProcedureTest();

        /// ProcedureTest destructor.
        ~ProcedureTest();

    private:
};

} // namespace hic

#endif // PROCEDURETEST_H 
