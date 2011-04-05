class CommandsItemTest
!!!186980.cpp!!!	test_method() : void
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
