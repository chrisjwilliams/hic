#include "CommandsItemTest.h"
#include "system/CommandsItem.h"
#include "system/LocalHost.h"
#include "system/Report.h"


namespace hic {

CPPUNIT_TEST_SUITE_REGISTRATION( CommandsItemTest );
/**
 * @details Constructs a CommandsItemTest object.
 */
CommandsItemTest::CommandsItemTest()
    : CppUnit::TestFixture()
{
}

/**
 * @details Destroys the CommandsItemTest object.
 */
CommandsItemTest::~CommandsItemTest()
{
}

void CommandsItemTest::setUp()
{
}

void CommandsItemTest::tearDown()
{
}

void CommandsItemTest::test_method()
{
    {
        // Use Case:
        // addCommand
        // Expect:
        // item to becomae valid and
        // command list to be updated
        LocalHost testhost; // TODO create a TestHost class
        CommandsItem item = CommandsItem( testhost );
        CPPUNIT_ASSERT( ! item.isValid() );
        item.appendCommand("testme");
        CPPUNIT_ASSERT( item.isValid() );
        Report r = item.exec();
        //CPPUNIT_ASSERT( item.commands() == testhost.lastExecuted() );
    }
}

} // namespace hic
