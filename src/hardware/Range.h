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
#ifndef HICRANGE_H
#define HICRANGE_H

#include <QList>
#include <QString>
#include <QStringList>
#include "StringConversion.h"
#include "system/Report.h"
#include <iostream>


/**
 * @file Range.h
 */

namespace hic {

/**
 * @class Range
 * 
 * @brief
 *    structure to define a range
 * @details
 *   the types can be any type that support the > and < operators
 * 
 */

template<typename T>
class Range
{
    public:
        /// Range constructor.
        Range() : _minSet(false), _maxSet(false), _stepSet(false) {};
        Range(const T& min, const T&max) : 
                  _minSet(false), _maxSet(false),_stepSet(false)
             { setMin(min); setMax(max); };

        /// Range destructor.
        ~Range() {};

        /// returns the minumum value in the range
        const T& min() const { return _min; }

        /// returns the maximum value of the range
        const T& max() const { return _max; };

        /// set the minimum value
        void setMin(const T& min) { 
            if( _maxSet && min > _max ) {
                _min = _max; _max = min;
            }
            else {
                _min = min; 
            }
            _minSet=true; 
        };

        /// set the maximum value
        void setMax(const T& max) { 
            if( _minSet && max < _min ) {
                _max = _min; _min = max;
            }
            else {
                _max = max; 
            }
            _maxSet=true; 
        };

        /// set the step size allowed
        void setStepSize(const T& step ) { _step = step; _stepSet = true; };

        /// returns true if there is a specific stepsize set
        bool hasStepSize() const { return _stepSet; };

        /// add a sub range
        Range<T> & operator+(const Range<T>& r)
        {
            if( ! r.isValid() )
                throw( QString("Range<t>::operator+:"
                               "attempt to add invalid range") );
            if( isValid() )
            {
                _subranges.append(r);
                if( r.min() < _min ) _min = r.min();
                if( r.max() > _max ) _max = r.max();
            }
            else {
                setMin( r.min() );
                setMax( r.max() );
            }
            return *this;
        }

        /// create an ascii string representatin of the range with the provided seperator
        QString toString(const QString& seperator = ":") const
        {
            if( ! isValid() )
                return "---";
           QString min = _toString(_min);
           QString max = _toString(_max);
           QString s = min;
           if( min != max ) s += seperator + max;
           return s;
        }

        /// converts a string of the format a<seperator>b into
        //  a range [a,b] 
        Report fromString(const QString& s, const QString& separator)
        {
            Report r;
            try {
                QStringList vals = s.split(separator);
                switch( vals.size()) {
                    case 1:
                        setMin( _fromString(vals.at(0)));
                        setMax( _fromString(vals.at(0)));
                        break;
                    case 2:
                        setMin( _fromString(vals.at(0)));
                        setMax( _fromString(vals.at(1)));
                        break;
                    default:
                        break;
                }
            }
            catch( const QString& error )
            {
                r.addErrorMessage(error);
            }
            return r;
        }

        /// returns true if the given range is the same as or 
        //  a valid subrange
        bool contains(const Range<T>& r) const
        {
            if( ! isValid() )
                return false;
            if( r.min() >= _min && r.max() <= _max )
                return true;
            return false;
        }

        /// returns true if a min,max value has been set
        //  false otherwise
        bool isValid() const { return _minSet && _maxSet; };

    protected:
        static T _fromString(const QString& s ) { 
            return Convertor<T>::fromString(s);
        };
        static QString  _toString(const T& t ) { 
            return Convertor<T>::toString(t);
        };

    private:
        T _step; // step size in the range
        QList<Range<T> > _subranges;
        mutable T _min;
        mutable T _max;
        bool _minSet;
        bool _maxSet;
        bool _stepSet;
};



} // namespace hic

#endif // HICRANGE_H 
