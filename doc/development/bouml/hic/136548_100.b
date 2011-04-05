class LCU_GeneratorTest
!!!170212.cpp!!!	test_method() : void
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
