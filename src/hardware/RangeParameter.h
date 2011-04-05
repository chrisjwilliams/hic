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
#ifndef RANGEPARAMETER_H
#define RANGEPARAMETER_H

#include <QList>
#include "Parameter.h"
#include "Range.h"

/**
 * @file RangeParameter.h
 */

namespace hic {

/**
 * @class RangeParameter
 * 
 * @brief
 *    Interface to describe various Range like parameters
 * @details
 * 
 */

template<typename T>
class RangeParameter : public Parameter<Range<T> >
{
    public:
        /// RangeParameter constructor.
        RangeParameter(const QString& name, const QString& doc)
            : Parameter<Range<T> >(ParameterQObject::Types::Range, name,doc)
        {}

        /// RangeParameter destructor.
        ~RangeParameter() {};

        /// returns a list of allowable ranges
        const QList<Range<T> >& allowableValues() const { return _allowed; }
        void setAllowableValues( const QList<Range<T> >& vals ) { 
            _allowed = vals;
            emit ParameterQObject::updated();
        };

    protected:
        QList<Range<T> > _allowed;

};

} // namespace hic

#endif // RANGEPARAMETER_H 
