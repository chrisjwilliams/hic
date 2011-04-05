class PlatformTest
!!!187620.cpp!!!	test_method() : void
    // Use Case:
    // copy doesn't cause problems
    Platform p1("test");
    Platform p2(p1);
    CPPUNIT_ASSERT( p2.name() == "test"  );
