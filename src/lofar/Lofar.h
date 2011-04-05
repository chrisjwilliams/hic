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
#ifndef LOFAR_H
#define LOFAR_H

#include <QList>
#include <boost/shared_ptr.hpp>
#include "hardware/Range.h"
#include "hardware/SelectionParameter.h"
#include "RCU.h"

/** const
 * @file Lofar.h
 */

namespace hic {
class RCU_Filter;

/**
 * @class Lofar
 * 
 * @brief
 *    Main class to hold objects relating to the Lofar subsystems
 * @details
 * 
 */
class Lofar
{
    public:
        /// Lofar constructor.
        Lofar();

        /// Lofar destructor.
        ~Lofar();

        /* 
         * Methods that allow State manipulation, via parameter objects
         */

        /// return the available clock speeds the array can run at
        //  in MHz
        boost::shared_ptr<SelectionParameter<float> > clockSpeeds() const;

        /* 
         * Methods to provide Information about the Lofar instrument
         */

        /// return available filters for a specific antenna array
        QList<RCU_Filter> filters(const RCU::Array&) const;

        /// return the range of RCU ids available in the specified array
        QList<Range<unsigned int> > rcuIds( const RCU::Array& ) const;

        /// return the base frequency for the given array
        float baseFrequency( const RCU::Array&, const RCU_Filter& ) const;

        /// return the array appropriate for the specified frequency
        RCU::Array array(float frequency, const RCU_Filter&) const;

        /// return the frequency for the given array and subband id
        float frequency( unsigned int subband_id, const RCU::Array&,
                         const RCU_Filter&,
                         float clock = -1.0 ) const;

        /// return the range of frequencies required
        Range<float> frequencyRange( const RCU::Array&, const RCU_Filter&,
                                     float clock ) const;

        /// return the width of each subband
        float subbandWidth( float clock ) const;

        QList<Range<unsigned int> > subbandRanges() const;

        /// return the subband corresponding to the specified frequency
        //  if clock <= 0.0 then it will take the value from the clockSpeeds()
        //  parameter
        unsigned int subband(float frequency, const RCU::Array&, const RCU_Filter&,
                             float clock  = -1.0);

    private:
        boost::shared_ptr<SelectionParameter<float> > _clock; 
};

} // namespace hic

#endif // LOFAR_H 
