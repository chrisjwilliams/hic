class RangeTest
!!!150372.cpp!!!	test_strings() : void
    // Use case:
    // String has a good range definition
    // Expect:
    // valid Range with correct min and max
    {
        Range<int> r;
        QString s("-10..24");
        r.fromString(s,"..");
        CPPUNIT_ASSERT( r.isValid() );
        CPPUNIT_ASSERT_EQUAL( -10, r.min() );
        CPPUNIT_ASSERT_EQUAL( 24, r.max() );
        CPPUNIT_ASSERT_EQUAL( s.toStdString(), r.toString("..").toStdString() );
    }

    // Use case:
    // String has bad characters
    // Expect:
    // not valid Range
    {
        Range<int> r;
        QString s("abc..24");
        r.fromString(s,"..");
        CPPUNIT_ASSERT( ! r.isValid() );
    }

    // Use case:
    // String has bad seperator
    // Expect:
    // not valid Range
    {
        Range<int> r;
        QString s("10...24");
        r.fromString(s,"..");
        CPPUNIT_ASSERT( ! r.isValid() );
    }
