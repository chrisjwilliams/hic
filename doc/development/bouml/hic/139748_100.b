class ProcedureTest
!!!188260.cpp!!!	test_empty() : void
    {
        // Use Case:
        // Empty Procedure
        // Expect
        // return invalid and do nothing on a call to exec()
        Procedure p;
        CPPUNIT_ASSERT( ! p.isValid() );
        Report r = p.exec();
        CPPUNIT_ASSERT( r.success() );
    }
!!!188388.cpp!!!	test_appendProcedure() : void
    {
        // Use Case:
        // Add an invalid Procedure
        // Expect:
        // No merge to take place, and status of orig to remain unchanged
        Procedure p;
        bool status = p.isValid();
        Procedure p2;
        CPPUNIT_ASSERT( ! p2.isValid() );
        p.appendProcedure(p2);
        CPPUNIT_ASSERT_EQUAL( status, p.isValid() );
    }
    {
        // Use Case:
        // Add a valid Procedure to an empty Procedure
        // Expect:
        // Merge to take place, and Procedure to become valid
        Procedure p;
        Procedure p2;
        TestProcedureItem testItem;
        p2.appendProcedure(testItem);
        CPPUNIT_ASSERT( p2.isValid() );
        p.appendProcedure( p2 );
        CPPUNIT_ASSERT( p.isValid() );
        // Use Case:
        // call exec on a valid procedure - no errors
        // Expect:
        // success report
        Report r = p.exec();
        CPPUNIT_ASSERT( r.success() );
    }
