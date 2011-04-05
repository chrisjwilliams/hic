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
#include "LofarBeam.h"
#include "Lofar.h"
#include "RCU.h"
#include "RCU_Filter.h"
#include <iostream>

namespace hic {

/**
 * @details Constructs a LofarBeam object.
 */
LofarBeam::LofarBeam( Lofar* lofar )
    : State(true), _lofar(lofar), _localUpdate(false)
{
    // construct parameters
    //_streams.reset(new MultiRangeParameter<unsigned int>(
   //                        "streams(beamlets)", 
    //                       "the output channels to map the subbands to. Max of 64 per beam is allowed") );
    //_streams.setRange( Range<unsigned int>(0,247) );

    _array.reset(new SelectionParameter<RCU::Array>(
                           "Antenna Array",
                           "Defines the Antenna array to use in this beam" ) );

    QList<QString> arrayDesc;  arrayDesc << "Low Band" 
                                         << "High Band";

    QList<RCU::Array> arrayValues;  arrayValues << RCU::LB << RCU::HB;
    _array->setAllowableValues( arrayDesc, arrayValues);


    _filter.reset( new SelectionParameter<RCU_Filter>(
                       "RCU Filter", 
                       "The filter to apply to the RCU chain") );

    _ids.reset( new MultiRangeParameter<unsigned int>(
                       "rcu id", 
                       "The ids of all rcu's to be included in the beam") );

    _frequency.reset( new SingleParameter<float>(
                       "frequency",
                       "The frequency range to observe" ) );

    _bandwidth.reset( new SingleParameter<float>(
                       "bandwidth",
                       "The width of the frequecy band to observe"
                       " relative to the start frequency" ) );

    _subbands.reset( new MultiRangeParameter<unsigned int>(
                       "subbands", 
                       "The subband identifiers associated with the frequen") );

    _directionType.reset( new SelectionParameter<QString>( 
                       "direction", "The type "
                       "of direction input. "
                       "SKYSCAN will scan the sky with a L x M grid in "
                       "the (l,m) plane") );
    _directionType->setAllowableValues( _direction.types(), _direction.types() );
    _directionType->set(_direction.types()[0]);

    _directionX.reset( new SingleParameter<float>("x", 
                   "The longitude in degrees for direction specification" ) );
    _directionX->setRange( Range<float>(-180,180) );
    _directionY.reset( new SingleParameter<float>("y", 
                   "The latitude in degrees for direction specification" ) );
    _directionY->setRange( Range<float>(-90.0,90.0) );
     updateDirection();

    // set default values (pre-connection)
    _frequency->set(0.0);
    _bandwidth->set(0.0);
    _setupConnections();

    // set default values
    _array->set(RCU::LB);
    refreshFilter();
    _filter->set(RCU_Filter());
    _ids->set( _lofar->rcuIds( _array->value()) );
    _subbands->set( _lofar->subbandRanges() );
    _subbands->setAllowableValues( _lofar->subbandRanges() );
    _directionX->set(0.0);
    _directionY->set(0.0);
    refreshFrequency();
    refreshRCU();

    // set up the RCU group
    ParameterGroup g("RCU Selection");
    g.addParameter( _array );
    g.addParameter( _filter );
    g.addParameter( _ids );

    // set up the frequency group
    ParameterGroup f("Frequency");
    f.addParameter( _frequency );
    f.addParameter( _bandwidth );
    f.addParameter( _subbands );

    // set up the direction group
    ParameterGroup d("Direction");
    d.addParameter( _directionType );
    d.addParameter( _directionX );
    d.addParameter( _directionY );

    appendGroup( g );
    appendGroup( f );
    appendGroup( d );
}

/**
 * @details Destroys the LofarBeam object.
 */
LofarBeam::~LofarBeam()
{
/*
    delete _streams;
    delete _array;
    delete _filter;
    delete _ids;
*/
}


LofarBeam* LofarBeam::clone() const
{
    LofarBeam* beam = new LofarBeam( *this );
    beam->_setupConnections(); // this will cause the
                               // signals to propagate to each copy independently.
                               // If there are multiple copies there will be
                               // some redundant calls to the underlying data
                               // types!
    return beam;
}

void LofarBeam::updateDirection()
{
    _direction.setLongitude( _directionX->value() );
    _direction.setLatitude( _directionY->value() );
    _direction.setType( _directionType->value() );
}

void LofarBeam::_setupConnections()
{
    // setup all the relationships between parameters
    connect( _array.get(), SIGNAL( updatedSelection() ), 
                      this, SLOT( refreshFilter() ) );
    connect( _array.get(), SIGNAL( updatedSelection() ), 
                      this, SLOT( refreshRCU() ) );
    connect( _array.get(), SIGNAL( updatedSelection() ), 
                      this, SLOT( refreshFrequency() ) );
    connect( _lofar->clockSpeeds().get(), SIGNAL( updatedSelection() ),
                      this, SLOT( clockUpdated() ) );
    connect( _frequency.get(), SIGNAL( updatedSelection() ),
                      this, SLOT( frequencyUpdate() ) );
    connect( _bandwidth.get(), SIGNAL( updatedSelection() ),
                      this, SLOT( bandwidthUpdate() ) );
    connect( _subbands.get(), SIGNAL( updatedSelection() ),
                      this, SLOT( subbandUpdate() ) );
    connect( _directionType.get(), SIGNAL( updatedSelection() ),
                      this, SLOT( updateDirection()) );
    connect( _directionX.get(), SIGNAL( updatedSelection() ),
                      this, SLOT( updateDirection()) );
    connect( _directionY.get(), SIGNAL( updatedSelection() ),
                      this, SLOT( updateDirection()) );
    //connect( _filter.get(), SIGNAL( updatedSelection() ),
    //                  this, SLOT( frequencyUpdate() ) );
}

/* routines to link parameters */
void LofarBeam::refreshFilter()
{
    QList<RCU_Filter> filters =  _lofar->filters( _array->value());
    QList<QString> descriptors;
    foreach( const RCU_Filter& filter, filters ) {
        descriptors.append( filter.name() );
    }
    _filter->setAllowableValues( descriptors, filters );
}

void LofarBeam::refreshRCU()
{
    _ids->setAllowableValues( _lofar->rcuIds( _array->value()) );
}

void LofarBeam::refreshFrequency()
{
    Range<float> range = _lofar->frequencyRange( _array->value(),
                                      _filter->value(),
                                      _lofar->clockSpeeds()->value() );
    _frequency->setRange( range );
    _bandwidth->setRange( Range<float>(0.0, range.max() - range.min()) );
    subbandUpdate();
}

void LofarBeam::clockUpdated()
{
    refreshFrequency();
}

// called whenever frequency param is updated
void LofarBeam::frequencyUpdate()
{
    if( _array->value() == RCU::undefined ) return;
    float start = _frequency->value();
    unsigned int minSubband = _lofar->subband( start, 
            _array->value(),
            _filter->value()
            );
    if( _subbands->min() != minSubband ) {
        _subbands->setMinimum( minSubband );
    }
    bandwidthUpdate();
}

// called whenever bandwidth param is updated
void LofarBeam::bandwidthUpdate()
{
    if( _array->value() == RCU::undefined ) return;
    float start = _frequency->value();
    unsigned int maxSubband = _lofar->subband( 
            start + _bandwidth->value() , _array->value(),
            _filter->value()
            );
    if( _subbands->max() != maxSubband ) {
        _subbands->setMaximum( maxSubband );
    }
}

// called whenever subband param is updated
void LofarBeam::subbandUpdate()
{
    float freq = _lofar->frequency( _subbands->min(), 
                                    _array->value(), 
                                    _filter->value() );
    float maxfreq = _lofar->frequency( _subbands->max(), 
                                       _array->value(), 
                                       _filter->value() );
    _frequency->set( freq );
    _bandwidth->set( maxfreq - freq );
}

/* routines to manipulate state */

void LofarBeam::setDirection(const BeamDirection& d)
{
    _direction = d;
}

void LofarBeam::setFilter(const RCU_Filter& filter)
{
    _filter->set(filter);
}

void LofarBeam::setRCU_ids(const QList<Range<unsigned int> >& ids )
{
    _ids->set(ids);
}

void LofarBeam::setSubbands(const QList<Range<unsigned int> >& sub )
{
    _subbands->set(sub);
}

void LofarBeam::setStreams( const Range<unsigned int>& streams )
{
    _streams->set(streams);
}

const Range<unsigned int>& LofarBeam::streams() const
{
    return _streams->value();
}

bool LofarBeam::isValid() const
{
    return    ( _array->value() != RCU::undefined )
           && ( _filter->value() != RCU_Filter() )
           && ( _ids->ranges().size() > 0 )
           //&& ( streams().min() < streams().max() )
           //&& ( _frequency.min() < _frequency.max() )
           && ( _subbands->ranges().size() > 0 )
           && ( _direction.isValid() );
}

} // namespace hic
