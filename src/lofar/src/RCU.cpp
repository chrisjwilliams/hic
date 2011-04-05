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
#include "RCU.h"
#include <QString>


namespace hic {

const RCU::filterMapT RCU::_filters = RCU::_init_map();

/**
 * @details Constructs a RCU object.
 */
RCU::RCU( const RCU::Array& array)
    : _array(array)
{
}

/**
 * @details Destroys the RCU object.
 */
RCU::~RCU()
{
}

RCU::filterMapT RCU::_init_map()
{
    filterMapT _filters;
    _filters[LB] << RCU_Filter("LBL 10MHz HPF")
        << RCU_Filter("LBL 30MHz HPF")
        << RCU_Filter("LBH 10MHz HPF")
        << RCU_Filter("LBH 30MHz HPF");
    _filters[HB] << RCU_Filter("HB 110-190MHz")
        << RCU_Filter("HB 210-270MHz");
    return _filters;
}

inline const QMap<RCU::Array, QList<RCU_Filter> >& RCU::filters() const
{
    return _filters;
}

void RCU::setFilter( const RCU_Filter& filter )
{
    if( ! filterOptions().contains(filter) )
        throw( QString("RCU_Filter %1 not available on this array") );

    _filter = filter;
}

QList<RCU_Filter> RCU::filterOptions() const
{
    return filters().value(_array);
}


} // namespace hic
