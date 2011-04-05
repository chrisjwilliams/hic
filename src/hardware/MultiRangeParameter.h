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
#ifndef MULTIRANGEPARAMETER_H
#define MULTIRANGEPARAMETER_H

#include <QString>
#include <QList>

#include "hardware/Range.h"
#include "MultiRangeParameterInterface.h"
#include "StringConversion.h"
#include "system/Report.h"
#include <iostream>
#include <QStringList>

/**
 * @file MultiRangeParameter.h
 */

namespace hic {

/**
 * @class MultiRangeParameter
 * 
 * @brief
 *   A parameter for describing multiple ranges
 * @details
 * 
 */

template<typename T>
class MultiRangeParameter : public MultiRangeParameterInterface
{
    public:
        typedef hic::Range<T> RangeT;
        typedef QList< RangeT > MultiRangeT;

    public:
        /// MultiRangeParameter constructor
        MultiRangeParameter(const QString& name, const QString& doc)
            : MultiRangeParameterInterface(name,doc)
            {};

        /// MultiRangeParameter destructor
        ~MultiRangeParameter() {};

        /// return the selected ranges
        const MultiRangeT& ranges() const { return _ranges; };

        const MultiRangeT& allowableRanges() const { return _allowed; };

        void setAllowableValues( const MultiRangeT& vals ) { 
            _allowed = vals;
            foreach( const Range<T>& r, vals )
            {
                if( ! _allowedRange.isValid() || r.max() > _allowedRange.max() )
                    _allowedRange.setMax(r.max());
                if( ! _allowedRange.isValid() || r.min() < _allowedRange.min() )
                    _allowedRange.setMin(r.min());
            }
            emit ParameterQObject::updated();
        };

        /// return a string representation of the minimum value
        //  of the allowed Range
        virtual QString minimum() const
        {
            if( !_allowedRange.isValid() )
                return QString("-");
            return _toString( _allowedRange.min() );
        }

        /// return a string representation of the minimum value
        //  of the allowed Range
        virtual QString maximum() const
        {
            if( !_allowedRange.isValid() )
                return QString("-");
            return _toString( _allowedRange.max() );
        }

        /// return the minimum value of all the SET ranges
        T min() const {
            if( _ranges.size() < 0 ) 
                throw QString("MultiRangeParameter: min() called with no Range set");
            T min = _ranges[0].min();
            foreach( const Range<T>& range, _ranges )
            {
                if( range.min() < min )
                    min = range.min();
            }
            return min;
        }

        /// return the minimum value for all the SET ranges
        T max() const {
            if( _ranges.size() < 0 ) 
                throw QString("MultiRangeParameter: max() called with no Range set");
            T max = _ranges[0].max();
            foreach( const Range<T>& range, _ranges )
            {
                if( range.max() < max )
                    max = range.max();
            }
            return max;
        }

        /// move the value of the lowest Range to the specified value
        void setMinimum(const T& min)
        {
            Range<T> range(min,min);;
            // simple case where no ranges exist
            if( _ranges.size() <= 0 ) {
                _ranges << range;
                emit updatedSelection();
                return;
            }
            if( _ranges[0].min() == min ) return;
            // remove all ranges that are less than the new minimum
            while( _ranges.size() > 0 && _ranges[0].max() < min )
            {
                _ranges.removeAt(0);
            }
            if( _ranges.size() > 0 )
            {
                _ranges[0].setMin(min);
            }
            else
            {
                _ranges << range;
            }
            emit updatedSelection();
        }

        /// move the value of the lowest Range to the specified value
        void setMaximum(const T& max)
        {
            Range<T> range(max,max);;
            if( _ranges.size() < 0 ) {
                _ranges << range;
            }
            else {
                if( _ranges.last().max() == max ) return;
                // remove all ranges that are > than the new max
                while( _ranges.size() > 0 && _ranges.last().min() > max )
                {
                    _ranges.removeLast();
                }
                if( _ranges.size() > 0 )
                {
                    _ranges.last().setMax(max);
                }
                else {
                    _ranges << range;
                }
            }
            emit updatedSelection();
        }

        /// set the ranges explicitly
        //  No attempt at validation
        void set(const MultiRangeT& ranges) {
            if( ranges.size() < 0 )
                return;

            // sort by minimum
            MultiRangeT sortList;
            sortList << ranges[0];
            for( int r = 1; r < ranges.size(); ++r )
            {
                bool inserted = false;
                for( int i = 0; i < sortList.size(); ++i )
                {
                    if( ranges[r].min() < sortList[i].min() )
                    {
                        sortList.insert(i, ranges[r]);
                        inserted = true;
                        break;
                    }
                }
                if ( ! inserted ) 
                    sortList << ranges[r];
            }
            // consolidate ranges
            int i=0;
            while( i < sortList.size() - 1 ) {
                if( sortList[i].max() >= sortList[i+1].min() )
                {
                    
                    sortList[i].setMax(sortList[i+1].max());
                    sortList.removeAt(++i);
                }
                ++i;
            }
            _ranges = sortList;
            emit updatedSelection();
        }


        /// validate a string
        Report validateString(const QString& s)
        {
            try {
                return validate(_fromString(s));
            }
            catch( const Report& r )
            {
                return r;
            }
        }

        virtual QString toString() const {
            QString s="";
            QString sep="";
            foreach( const RangeT& range, _ranges ) {
                s += sep + range.toString(_rangeCont);
                sep = _rangeSeparator;
            }
            return s;
        }

        /// ensure that the set values are within the given ranges
        Report validate(const MultiRangeT& ranges)
        {
            Report r;
            foreach( const RangeT& range, ranges ) {
                // if valid ranges are not set, then we assume taht anything is OK
                bool found = (_allowed.size() == 0 )?true:false;
                // check it is with the valid ranges
                foreach( const RangeT& a, _allowed ) {
                    if( a.contains(range) ) found = true;
                }
                if( ! found ) {
                    r.addErrorMessage(QString("invalid range :") 
                                      + range.toString());
                }
            }
            return r;
        }

    protected:
        /// set the Ranges from a String if it is valid
        //  returns a Report object to indicate success
        virtual Report _setFromString(const QString& s)
        {
            Report r;
            MultiRangeT ranges = _fromString(s);
            r = validate(ranges);
            if( r.success() )
            {
                _ranges = _fromString(s);
            }
            return r;
        }

        /// convert string from the ranges
        //  each separate range should be spereated by a ","
        MultiRangeT _fromString(const QString& str)
        {
             Report r;
             r.addMessage(QString("Parsing range definition:") + str);
             MultiRangeT ranges;
             foreach( const QString& s, str.split(_rangeSeparator) )
             {
                 Range<T> sub;
                 sub.fromString(s, _rangeCont );
                 if( ! sub.isValid() )
                 {
                     r.addErrorMessage(QString("Invalid Range definition:") + s );
                 }
                 ranges.append(sub);
             }
             if( ! r.success() ) throw r;
             return ranges;
        }

        QString _toString(const T& t) const {
            return Convertor<T>::toString(t);
        }


    protected:
        MultiRangeT _allowed; // allows for multiple disjoint ranges
        RangeT _allowedRange; // records the extremes of all allowed ranges

    private:
        MultiRangeT _ranges; // actual selections made from the allowed ranges
};

} // namespace hic

#endif // MULTIRANGEPARAMETER_H
