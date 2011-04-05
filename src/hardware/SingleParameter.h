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
#ifndef SINGLEPARAMETER_H
#define SINGLEPARAMETER_H


#include "SingleParameterInterface.h"
#include "hardware/Range.h"
#include "StringConversion.h"

/**
 * @file SingleParameter.h
 */

namespace hic {
    class Report;

/**
 * @class SingleParameter
 * 
 * @brief
 *    A parameter for a single value with an optional range restraint
 * @details
 * 
 */

template<typename T>
class SingleParameter : public SingleParameterInterface 
{
    public:
        /// SingleParameter constructor.
        SingleParameter( const QString& name, const QString& doc ) 
                : SingleParameterInterface(name,doc) {};

        /// SingleParameter destructor.
        ~SingleParameter() {};

        // reqs of base class
        virtual bool hasRange() const {
            return _allowedRange.isValid();
        };

        /// return a string representation of the minimum value
        virtual QString minimum() const
        {
            if( !_allowedRange.isValid() )
                return QString("-");
            return _toString( _allowedRange.min() );
        }

        /// return a string representation of the minimum value
        virtual QString maximum() const
        {
            if( !_allowedRange.isValid() )
                return QString("-");
            return _toString( _allowedRange.max() );
        }

        virtual Report validateString(const QString& s)
        {
            Report r;
            try {
                if( ! validate( _fromString(s) ) )
                    r.addErrorMessage(QString("parameter ") + name() + " invalid value: " + s);
            }
            catch( const QString& msg ) {
                r.addErrorMessage(msg);
            }

            return r;
        }

        /// return the vlaue as a string constant
        virtual QString toString() const { return _toString( value() ); }

        /// return the set value
        const T& value() const { return _value; };

        /// set the value
        bool set(const T& value) { 
            if( value == _value )
                return true;
            bool r = validate(value);
            if( r ) {
                _value = value; 
                emit updatedSelection();
            }
            return r;
        };

        /// sets the valid range for the values
        void setRange( const Range<T>& range ) { 
            verbose(QString("setRange ") + range.toString() );
            _allowedRange = range; 
            emit updated();
        };

        /// return the range allowed from the value
        const Range<T>& range() const { return _allowedRange; };

        /// validate the value
        bool validate(const T& value) { 
            bool r = true;
            if( _allowedRange.isValid() &&  ! _allowedRange.contains( Range<T>(value,value)) )
            {
                r = false;
                std::cout << "SingleParameter::validate() :'" << name().toStdString() << "':"
                          << _toString(value).toStdString() << " not valid."
                          " valid range(" << _allowedRange.toString(",").toStdString() << ")" <<std::endl;
            }
            return r;
        };

        /// required functions from base class
        virtual Report _setFromString( const QString& s) 
        {
            Report r;
            try {
                if( ! set( _fromString(s) ) ) 
                    r.addErrorMessage("invalid data");
            }
            catch( const QString& msg ) {
                r.addErrorMessage(msg);
            }
            return r;
        };

    protected:
        T _fromString(const QString& s) const { 
            return Convertor<T>::fromString(s);
        };
        QString _toString(const T& s) const {
            return Convertor<T>::toString(s);
        }


    private:
        T _value;
        Range<T> _allowedRange;

};

} // namespace hic

#endif // SINGLEPARAMETER_H 
