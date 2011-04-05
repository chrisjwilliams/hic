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
#ifndef SELECTIONPARAMETER_H
#define SELECTIONPARAMETER_H


#include "SelectionParameterInterface.h"
#include <iostream>

/**
 * @file SelectionParameter.h
 */

namespace hic {

/**
 * @class SelectionParameter
 * 
 * @brief
 *   Templated extension to the base SelectionParameterInterface
 * @details
 *   provide a value mapping from the descriptors
 * 
 */
template<typename T>
class SelectionParameter : public SelectionParameterInterface
{
    public:
        /// SelectionParameter constructor.
        SelectionParameter(const QString& name, const QString& doc)
            : SelectionParameterInterface( name, doc) { };

        /// SelectionParameter destructor.
        ~SelectionParameter() {};

        void setAllowableValues( const QList<QString>& descriptors, const QList<T>& vals ) { 
            _allowable = descriptors;
            _allowableVals = vals;
            emit updated();
        };

        void set( const T& val ) {
            int current = _allowableVals.indexOf(val);
            if( current >= 0 && current != _currentIndex )
            {
                _currentIndex = current;
                emit ParameterQObject::updatedSelection();
            }
        }

        const QList<T>& allowedVals() const { return _allowableVals; };

        const T& value() const { 
            verbose(QString("value() current item is number ") + 
                    QString().setNum(_currentIndex) + " of " + 
                    QString().setNum(_allowableVals.size()) );
            return _allowableVals[_currentIndex];
        }

    private:
        QList<T> _allowableVals;
};

} // namespace hic

#endif // SELECTIONPARAMETER_H 
