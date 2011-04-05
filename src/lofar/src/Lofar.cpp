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
#include "Lofar.h"
#include <QList>
#include "RCU.h"
#include "RCU_Filter.h"
#include "hardware/Range.h"


namespace hic {


/**
 * @details Constructs a Lofar object.
 */
Lofar::Lofar()
{
    // setup the clock parameter
    _clock.reset(new SelectionParameter<float>(QObject::tr("clock"), 
        "The clock frequency that the telescope is set") );
    QList<QString> clockLabels; clockLabels << "160 Mhz" << "200 MHz";
    QList<float> clockVals; clockVals << 160.0 << 200.0;
    _clock->setAllowableValues( clockLabels, clockVals );
}

/**
 * @details Destroys the Lofar object.
 */
Lofar::~Lofar()
{
}

boost::shared_ptr<SelectionParameter<float> > Lofar::clockSpeeds() const
{
    return _clock;
}


QList<RCU_Filter> Lofar::filters(const RCU::Array& array) const
{
    RCU r(array);
    return r.filterOptions();
}

QList<Range<unsigned int> > Lofar::rcuIds(const RCU::Array& /*array*/) const
{
   QList<Range<unsigned int> > list;
   Range<unsigned int> r(0,191);
   list.append(r);
   return list; 
}

float Lofar::baseFrequency(const RCU::Array& array, const RCU_Filter& filter) const
{
    float r = 0.0;
    switch( array ) {
        case RCU::LB:
            r = 0.0;
            {
                switch( filter.filterId() ) {
                    case RCU_Filter::UNSET:
                        break;
                    case RCU_Filter::LBL_10MHz_HPF:
                        break;
                    case RCU_Filter::LBL_30MHz_HPF:
                        break;
                    case RCU_Filter::LBH_10MHz_HPF:
                        break;
                    case RCU_Filter::LBH_30MHz_HPF:
                        break;
                    default:
                        break;
                }
            }
            break;
        case RCU::HB:
            r = 100.0;
            {
                switch( filter.filterId() ) {
                    case RCU_Filter::UNSET:
                        break;
                    case RCU_Filter::HB_110MHz:
                        r=110.0;
                        break;
                    case RCU_Filter::HB_170MHz:
                        r=170.0;
                        break;
                    case RCU_Filter::HB_210MHz:
                        r=210.0;
                        break;
                    default:
                        break;
                }
            }
            break;
        default:
            break;
    }
    return r;
}

Range<float> Lofar::frequencyRange( const RCU::Array& array, 
                                    const RCU_Filter& filter,
                                    float clock ) const
{
    /// beamlets range from 0..511. Each beamlet represents
    //  a bandwidth of (512/(number of beams))
    float base = baseFrequency(array, filter);
    float max = frequency(511, array, filter, clock );
    int stepSize = (max-base)/512;
    Range<float> r(base, max - stepSize );
    r.setStepSize(stepSize);
    return r;
}

float Lofar::frequency( unsigned int subband_id, const RCU::Array& array,
                        const RCU_Filter& filter,
                        float clock ) const
{
    float mclock = clock;
    if( mclock <= 0.0 ) mclock = _clock->value();
    float freq = baseFrequency(array, filter) + 
                 subband_id * subbandWidth( mclock );
    return freq;
}

unsigned int Lofar::subband(float frequency, const RCU::Array& array, 
                            const RCU_Filter& filter,
                            float clock )
{
    float mclock = clock;
    if( mclock <= 0.0 ) mclock = _clock->value();
    Range<float> fspan = frequencyRange( array, filter, mclock );
    int s = (int)((frequency - fspan.min())/subbandWidth( mclock ));
    return s;
}

QList<Range<unsigned int> > Lofar::subbandRanges() const
{
    QList<Range<unsigned int> > list;
    Range<unsigned int> r(0,511);
    list << r;
    return list;
}

float Lofar::subbandWidth( float clock ) const
{
    return (clock/2.0)/512.0;
}

} // namespace hic
