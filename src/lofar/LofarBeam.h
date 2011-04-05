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
