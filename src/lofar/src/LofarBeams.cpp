#include "LofarBeams.h"
#include <QObject>
#include <QList>
#include <QString>
#include "hardware/ParameterGroup.h"
#include "hardware/SelectionParameter.h"


namespace hic {


/**
 * @details Constructs a LofarBeams object.
 */
LofarBeams::LofarBeams()
{
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
}

/**
 * @details Destroys the LofarBeams object.
 */
LofarBeams::~LofarBeams()
{
    foreach( LofarBeam* beam, _beams )
    {
        delete beam;
    }
}

/*
LofarBeams* LofarBeams::clone() const
{
    return new LofarBeams( *this );
}
*/

void LofarBeams::addBeam(LofarBeam* beam)
{
    //LofarBeam* clone = beam.clone();
    _beams.append(beam);
    _states.append(beam);

}

} // namespace hic
