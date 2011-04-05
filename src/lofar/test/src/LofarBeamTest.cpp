#include "LofarBeamTest.h"
#include "LofarBeam.h"
#include "Lofar.h"


namespace hic {

CPPUNIT_TEST_SUITE_REGISTRATION( LofarBeamTest );
/**
 * @details Constructs a LofarBeamTest object.
 */
LofarBeamTest::LofarBeamTest()
    : CppUnit::TestFixture()
{
}

/**
 * @details Destroys the LofarBeamTest object.
 */
LofarBeamTest::~LofarBeamTest()
{
}

void LofarBeamTest::setUp()
{
}

void LofarBeamTest::tearDown()
{
}

void LofarBeamTest::test_frequencySetting()
{
    Lofar lofar;
    { // Use Case:
      // set start frequency in range, no subbands set, no array explicitly set
      // Expect:
      // array and frequency set, subbands contains single appropriate value
      LofarBeam l(&lofar);
      lofar.clockSpeeds()->set(200);
      l.setFrequency(0.0);
      CPPUNIT_ASSERT_EQUAL( 1, l.subbands().size() );
      CPPUNIT_ASSERT_EQUAL( RCU::LB, l.array() );
      CPPUNIT_ASSERT_EQUAL( (unsigned int)0, l.subbands()[0].min() );
      CPPUNIT_ASSERT_EQUAL( (unsigned int)511 , l.subbands()[0].max() );

      // try another value on the same array
      l.setFrequency(10.00);
      float sw = lofar.subbandWidth( 200 );
      CPPUNIT_ASSERT_EQUAL( 1, l.subbands().size() );
      CPPUNIT_ASSERT_EQUAL( RCU::LB, l.array() );
      CPPUNIT_ASSERT_EQUAL( (unsigned int)(10.0/sw), l.subbands()[0].min() );
      CPPUNIT_ASSERT_EQUAL( (unsigned int)511, l.subbands()[0].max() );

      // set the bandwidth
      // expect max of subbands to move to
      // the correct band
      l.setBandwidth(10.00);
      CPPUNIT_ASSERT_EQUAL( 1, l.subbands().size() );
      CPPUNIT_ASSERT_EQUAL( (unsigned int)(10.0/sw), l.subbands()[0].min() );
      CPPUNIT_ASSERT_EQUAL( (unsigned int)(20.0/sw), l.subbands()[0].max() );
    }
    {
      // Use case:
      // set only bandwidth without setting frequency first
      // Expect:
      // subband start to take minimum value
      // subband max to be that offset from min
      LofarBeam l(&lofar);
      float clock = lofar.clockSpeeds()->allowedVals()[0];
      lofar.clockSpeeds()->set(clock);
      float sw = lofar.subbandWidth( clock );
      l.setBandwidth( 10.0 );
      CPPUNIT_ASSERT_EQUAL( 1, l.subbands().size() );
      CPPUNIT_ASSERT_EQUAL( (unsigned int)0, l.subbands()[0].min() );
      CPPUNIT_ASSERT_EQUAL( (unsigned int)(10.0/sw), l.subbands()[0].max() );
      // Use case:
      // set a frequency
      // Expect:
      // correct lower subband, upper subband to move to previous bandwidth
      // relative to this 
      l.setFrequency(10.00);
      CPPUNIT_ASSERT_EQUAL( 1, l.subbands().size() );
      CPPUNIT_ASSERT_EQUAL( (unsigned int)(10.0/sw), l.subbands()[0].min() );
      CPPUNIT_ASSERT_EQUAL( (unsigned int)(20.0/sw), l.subbands()[0].max() );
    }
}

void LofarBeamTest::test_subbandSetting()
{
    
}

/*
void LofarBeamTest::test_clone()
{
    Lofar lofar;

    // Use case:
    // Ensure we can clone an object
    LofarBeam* copy;
    {
        LofarBeam l(&lofar);
        CPPUNIT_ASSERT( ! l.isValid() );
        copy = l.clone();
        // exit scope to kill off original object
        // copy should still be a viable object
    }
    CPPUNIT_ASSERT( ! copy->isValid() );
}
*/

} // namespace hic
