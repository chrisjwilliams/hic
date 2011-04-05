#ifndef LOFARBEAM_H
#define LOFARBEAM_H

#include <QString>

#include "State.h"
#include "RCU.h"
#include "RCU_Filter.h"
#include "BeamDirection.h"
#include "hardware/Range.h"
#include "hardware/RangeParameter.h"
#include "hardware/MultiRangeParameter.h"
#include "hardware/SelectionParameter.h"
#include "hardware/SingleParameter.h"
#include <boost/shared_ptr.hpp>

/**
 * @file LofarBeam.h
 */

namespace hic {
class Lofar;

/**
 * @class LofarBeam
 * 
 * @brief
 *   A Beam view of the State of a Lofar Station
 * @details
 * 
 */
class LofarBeam : public State
{
    Q_OBJECT

    public:
        /// LofarBeam constructor.
        LofarBeam( Lofar* lofar );
        //LofarBeam();

        /// LofarBeam destructor.
        ~LofarBeam();

        /// the direction of the beam
        const BeamDirection& direction() const { return _direction; };
        void setDirection(const BeamDirection&);

        /// the rcu filter mode applied to all rcu in the beam
        const RCU_Filter& filter() const { return _filter->value(); };
        void setFilter(const RCU_Filter& filter);

        /// the array to be used in the beam
        RCU::Array array() const { return _array->value(); };
        void setArray(const RCU::Array& array ) { _array->set(array); };

        /// the rcu to include in the beam
        const QList<Range<unsigned int> >& RCU_Ids() const { return _ids->ranges(); };
        void setRCU_ids(const QList<Range<unsigned int> >& ids );

        /// The subband range
        const QList<Range<unsigned int> >& subbands() const { return _subbands->ranges(); };
        void setSubbands(const QList<Range<unsigned int> >& subbands );

        /// The output stream channels to map the subbands onto
        const Range<unsigned int>& streams() const;
        void setStreams( const Range<unsigned int>& );

        /// the minimum frequency represented by the subbands
        float frequency() const { return _frequency->value(); };
        void setFrequency(float mhz) { _frequency->set(mhz); };

        /// the bandwidth
        float bandwidth() const { return _bandwidth->value(); };
        void setBandwidth( float b ) { _bandwidth->set(b); };

        /// returns true if the dataset for the beam is complete
        bool isValid() const;

        /// requirement of base class to 
        LofarBeam* clone() const;

    public slots:
        void refreshFilter();
        void refreshRCU();
        void refreshFrequency();
        void clockUpdated();
        void frequencyUpdate();
        void bandwidthUpdate();
        void subbandUpdate();
        void updateDirection();

    private:
        void _setupConnections();

    private:
        Lofar*  _lofar;
        boost::shared_ptr<SelectionParameter<RCU::Array > > _array;
        boost::shared_ptr<RangeParameter<unsigned int> >  _streams;
        boost::shared_ptr<SelectionParameter<RCU_Filter > > _filter;
        boost::shared_ptr<MultiRangeParameter<unsigned int> > _ids;
        //Range<unsigned int> _streams; // mapping of subbands to stream channels
        boost::shared_ptr<SingleParameter<float> > _frequency;
        boost::shared_ptr<SingleParameter<float> > _bandwidth;
        boost::shared_ptr<MultiRangeParameter<unsigned int> > _subbands;
        boost::shared_ptr<SingleParameter<float> > _directionX;
        boost::shared_ptr<SingleParameter<float> > _directionY;
        boost::shared_ptr<SelectionParameter<QString> > _directionType;

        BeamDirection _direction;
        float _clock;
        bool _localUpdate;
};

} // namespace hic

#endif // LOFARBEAM_H ;
