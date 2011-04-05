#include "RangeTest.h"
#include "Range.h"


namespace hic {

CPPUNIT_TEST_SUITE_REGISTRATION( RangeTest );
/**
 * @details Constructs a RangeTest object.
 */
RangeTest::RangeTest()
    : CppUnit::TestFixture()
{
}

/**
 * @details Destroys the RangeTest object.
 */
RangeTest::~RangeTest()
{
}

void RangeTest::setUp()
{
}

void RangeTest::tearDown()
{
}

void RangeTest::test_strings()
{
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
}

} // namespace hic
