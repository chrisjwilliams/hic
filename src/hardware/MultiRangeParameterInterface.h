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
