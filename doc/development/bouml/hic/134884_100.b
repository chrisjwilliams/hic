class LofarBeams
!!!166500.cpp!!!	LofarBeams()
    setName("LofarBeams");

    // Main Instrument Definitions
    ParameterGroup g(QString("Lofar Settings"));
    g.addParameter(_lofar.clockSpeeds() );
    appendGroup(g);

    // setup the beam parameter groups
    int maxBeams = 8; // Lofar can support up to 8 beams
    for(int i=0; i < maxBeams; ++i )
    {
        ParameterGroup g(QString("Beam %1").arg( i+1 ));
        LofarBeam* beam = new LofarBeam( &_lofar );
        beam->setName(QString("Beam %1").arg( i+1 ));
        //beam.setChannel(i/2);
        addBeam(beam);
        g.enableDeactivation();
        if( i != 0 ) {
            g.setActiveState(false);
            beam->setActiveMode(false);
        }

/*
        Parameter dataStream(QObject::tr("Stream"), "The Stream on which to output the data. Maximum of 2 beams per Channel");
        QMap<QString,QString> dataStreamOptions;
        dataStreamOptions["Channel 1"] = "1";
        dataStreamOptions["Channel 2"] = "2";
        dataStreamOptions["Channel 3"] = "3";
        dataStreamOptions["Channel 4"] = "4";
        dataStream.setRestrictedValues( dataStreamOptions );
        g.addParameter(dataStream);
*/

        // add the finished group to the class
        //_groups.append(g);
    }
!!!166628.cpp!!!	~LofarBeams()
    foreach( LofarBeam* beam, _beams )
    {
        delete beam;
    }
!!!166756.cpp!!!	addBeam(inout beam : LofarBeam) : void
    //LofarBeam* clone = beam.clone();
    _beams.append(beam);
    _states.append(beam);

