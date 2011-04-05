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
