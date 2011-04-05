/*
 * Copyright (c) 2011, The University of Oxford
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the University of Oxford nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
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
