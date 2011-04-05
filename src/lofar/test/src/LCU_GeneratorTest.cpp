#include "LCU_GeneratorTest.h"
#include "LCU_Generator.h"
#include "LofarBeams.h"
#include "system/Procedure.h"
#include "lofar/Lofar.h"
#include "lofar/BeamDirection.h"
#include "lofar/RCU.h"
#include "lofar/RCU_Filter.h"
#include "system/Report.h"
#include "hardware/test/TestState.h"


namespace hic {

CPPUNIT_TEST_SUITE_REGISTRATION( LCU_GeneratorTest );
/**
 * @details Constructs a LCU_GeneratorTest object.
 */
LCU_GeneratorTest::LCU_GeneratorTest()
    : CppUnit::TestFixture()
{
}

/**
 * @details Destroys the LCU_GeneratorTest object.
 */
LCU_GeneratorTest::~LCU_GeneratorTest()
{
}

void LCU_GeneratorTest::setUp()
{
}

void LCU_GeneratorTest::tearDown()
{
}

void LCU_GeneratorTest::test_method()
{
    {
        // Use case:
        // State of the incorrect type passed
        // Expect:
        // An empty procedure to be returned
        LCU_Generator gen;
        TestState state;
        Procedure p = gen.setState(state);
        CPPUNIT_ASSERT( ! p.isValid() );
    }
    {
        // Use case:
        // State of the correct type passed but has no content
        // Expect:
        // An empty procedure to be returned
        LCU_Generator gen;
        LofarBeams state;
        Procedure p = gen.setState(state);
        CPPUNIT_ASSERT( ! p.isValid() );
    }
    {
        // Use case:
        // State of the correct type passed with a single invalid beam
        // Expect:
        // Invalid Procedure
        LCU_Generator gen;
        // setup the state
        LofarBeams state;
        Lofar lofar;
        LofarBeam beam(&lofar);
        CPPUNIT_ASSERT( ! beam.isValid() );
        state.addBeam(beam);

        Procedure p = gen.setState(state);
        CPPUNIT_ASSERT(  ! p.isValid() );
    }
    {
        // Use case:
        // State of the correct type passed with a single beam
        // Expect:
        // Procedure to generate the beam profile
        LCU_Generator gen;
        // setup the state
        LofarBeams state;
        Lofar lofar;
        LofarBeam beam(&lofar);
        BeamDirection dir(0.0,0.0,"SOMETHING");
        beam.setDirection(dir);
        beam.setFilter( RCU_Filter("LBL 10MHz HPF") );
        beam.setArray(RCU::LB);
        Range<unsigned int> streams(1,3);
        beam.setStreams(streams);
        QList<Range<unsigned int> > subbands;
                           subbands << Range<unsigned int>(1,30);
        beam.setRCU_ids( subbands );
        beam.setSubbands(subbands);
        CPPUNIT_ASSERT( beam.isValid() );
        state.addBeam(beam);

        Procedure p = gen.setState(state);
        CPPUNIT_ASSERT(  p.isValid() );
        
        Report r = p.exec();

        // try via the State& interface
        State& stateS = static_cast<State&>(state);
        Procedure p2 = gen.setState(stateS);
        CPPUNIT_ASSERT(  p2.isValid() );

    }
}

} // namespace hic
