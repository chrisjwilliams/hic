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
#ifndef MULTIRANGEPARAMETERINTERFACE_H
#define MULTIRANGEPARAMETERINTERFACE_H

#include <QString>
#include "ParameterQObject.h"

/**
 * @file MultiRangeParameterInterface.h
 */

namespace hic {
    class Report;

/**
 * @class MultiRangeParameterInterface
 * 
 * @brief
 *    Base interface methods for MultiRangeParameter types
 * @details
 * 
 */
class MultiRangeParameterInterface : public ParameterQObject
{
    public:
        /// MultiRangeParameterInterface constructor.
        MultiRangeParameterInterface( const QString& name, const QString& doc );

        /// MultiRangeParameterInterface destructor.
        virtual ~MultiRangeParameterInterface();

        /// return the characters used for range seperation in string formats
        inline const QString& rangeSeperator() const { return _rangeSeparator; };

        /// return the characters used for range spanning
        inline const QString& spanIndicator() const { return _rangeCont; };

        /// return a string representation of the minimum value
        virtual QString minimum() const = 0;

        /// return a string representation of the minimum value
        virtual QString maximum() const = 0;

        /// set the Ranges from a String
        //virtual Report setFromString(const QString&) = 0;

        /// validate a string
        virtual Report validateString(const QString&) = 0;

        virtual QString toString() const = 0;

    protected:
        QString _rangeSeparator;
        QString _rangeCont;
};

} // namespace hic

#endif // MULTIRANGEPARAMETERINTERFACE_H 
