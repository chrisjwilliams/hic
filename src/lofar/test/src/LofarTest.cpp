#include "LofarTest.h"
#include "Lofar.h"


namespace hic {

CPPUNIT_TEST_SUITE_REGISTRATION( LofarTest );
/**
 * @details Constructs a LofarTest object.
 */
LofarTest::LofarTest()
    : CppUnit::TestFixture()
{
}

/**
 * @details Destroys the LofarTest object.
 */
LofarTest::~LofarTest()
{
}

void LofarTest::setUp()
{
}

void LofarTest::tearDown()
{
}

void LofarTest::test_ranges()
{
    Lofar f;
    float clock = 200;
    {
    // Use Case:
    // LBA with no filter
    // Expect:
    // 0..100MHz
        Range<float> expect(0,100.0 - f.subbandWidth(clock) );
        CPPUNIT_ASSERT_EQUAL( expect.toString().toStdString(), 
                              f.frequencyRange(RCU::LB, RCU_Filter(), clock ).toString().toStdString() );
    }

}

void LofarTest::test_subbandWidth()
{
    Lofar f;
    CPPUNIT_ASSERT_EQUAL( (float)0.1562500, f.subbandWidth( 160 ) );
    CPPUNIT_ASSERT_EQUAL( (float)0.1953125 , f.subbandWidth( 200 ) );
}

void LofarTest::test_subband()
{
    // Use Case:
    // test the subband for 0 frequency and LB
    // expect a subband of 0
    Lofar f;
    float clock = 200;
    CPPUNIT_ASSERT_EQUAL( 0, (int)f.subband(0,RCU::LB, RCU_Filter(), clock ) );
    // test the subband for max frequency and LB
    // expect a subband of 511
    float max = f.frequencyRange(RCU::LB, RCU_Filter(), clock ).max();
    CPPUNIT_ASSERT_EQUAL( 511, (int)f.subband( max ,RCU::LB, RCU_Filter(), clock) );

    // Use Case:
    // minimum value of High Frequency Array
    // expect a subband of 0
    float min = f.frequencyRange(RCU::HB, RCU_Filter(), clock ).min();
    CPPUNIT_ASSERT_EQUAL( 0, (int)f.subband(min,RCU::HB, RCU_Filter(), clock ) );
    
}


} // namespace hic
