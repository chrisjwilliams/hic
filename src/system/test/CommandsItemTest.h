#ifndef COMMANDSITEMTEST_H
#define COMMANDSITEMTEST_H

#include <cppunit/extensions/HelperMacros.h>

/**
 * @file CommandsItemTest.h
 */

namespace hic {

/**
 * @class CommandsItemTest
 * 
 * @brief
 *   unit test for CommandsItem
 * @details
 * 
 */
class CommandsItemTest : public CppUnit::TestFixture
{
    public:
        CPPUNIT_TEST_SUITE( CommandsItemTest );
        CPPUNIT_TEST( test_method );
        CPPUNIT_TEST_SUITE_END();

    public:
        void setUp();
        void tearDown();

        // Test Methods
        void test_method();

    public:
        /// CommandsItemTest constructor.
        CommandsItemTest();

        /// CommandsItemTest destructor.
        ~CommandsItemTest();

    private:
};

} // namespace hic

#endif // COMMANDSITEMTEST_H 
