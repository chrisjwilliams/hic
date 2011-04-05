class Lofar
!!!161252.cpp!!!	Lofar()
    // setup the clock parameter
    _clock.reset(new SelectionParameter<float>(QObject::tr("clock"), 
        "The clock frequency that the telescope is set") );
    QList<QString> clockLabels; clockLabels << "160 Mhz" << "200 MHz";
    QList<float> clockVals; clockVals << 160.0 << 200.0;
    _clock->setAllowableValues( clockLabels, clockVals );
!!!161508.cpp!!!	clockSpeeds() : boost::shared_ptr<SelectionParameter<float> >
    return _clock;
!!!161636.cpp!!!	filters(in array : Array) : QList<RCU_Filter>
    RCU r(array);
    return r.filterOptions();
!!!161764.cpp!!!	rcuIds(in  : Array) : QList<Range<unsigned int> >
   QList<Range<unsigned int> > list;
   Range<unsigned int> r(0,191);
   list.append(r);
   return list; 
!!!161892.cpp!!!	baseFrequency(in array : Array, in filter : RCU_Filter) : float
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
!!!162276.cpp!!!	frequencyRange(in array : Array, in filter : RCU_Filter, in clock : float) : Range<float>
    /// beamlets range from 0..511. Each beamlet represents
    //  a bandwidth of (512/(number of beams))
    float base = baseFrequency(array, filter);
    float max = frequency(511, array, filter, clock );
    int stepSize = (max-base)/512;
    Range<float> r(base, max - stepSize );
    r.setStepSize(stepSize);
    return r;
!!!162148.cpp!!!	frequency(in subband_id : uint, in array : Array, in filter : RCU_Filter, in clock : float = -1.0) : float
    float mclock = clock;
    if( mclock <= 0.0 ) mclock = _clock->value();
    float freq = baseFrequency(array, filter) + 
                 subband_id * subbandWidth( mclock );
    return freq;
!!!162660.cpp!!!	subband(in frequency : float, in array : Array, in filter : RCU_Filter, in clock : float = -1.0) : uint
    float mclock = clock;
    if( mclock <= 0.0 ) mclock = _clock->value();
    Range<float> fspan = frequencyRange( array, filter, mclock );
    int s = (int)((frequency - fspan.min())/subbandWidth( mclock ));
    return s;
!!!162532.cpp!!!	subbandRanges() : QList<Range<unsigned int> >
    QList<Range<unsigned int> > list;
    Range<unsigned int> r(0,511);
    list << r;
    return list;
!!!162404.cpp!!!	subbandWidth(in clock : float) : float
    return (clock/2.0)/512.0;
