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
