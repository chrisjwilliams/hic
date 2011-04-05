class StateControllerTest
!!!130020.cpp!!!	test_method() : void
    {
        // Use Case:
        // No generators
        // Expect:
        // success report
        StateController sc;
        TestState state;
        Report r = sc.setState(state);
        CPPUNIT_ASSERT( r.success() );
    }
    {
        StateController sc;
        TestState state;
        sc.addGenerator(new TestGenerator);
        Report r = sc.setState(state);
        CPPUNIT_ASSERT( r.success() );
    }
