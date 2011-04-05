#ifndef SINGLEPARAMETERINTERFACE_H
#define SINGLEPARAMETERINTERFACE_H

#include <QString>
#include "ParameterQObject.h"

/**
 * @file SingleParameterInterface.h
 */

namespace hic {
    class Report;

/**
 * @class SingleParameterInterface
 * 
 * @brief
 *    Base class for the Single parameter
 * @details
 * 
 */
class SingleParameterInterface : public ParameterQObject
{
    public:
        /// SingleParameterInterface constructor.
        SingleParameterInterface( const QString& name, const QString& doc );

        /// SingleParameterInterface destructor.
        ~SingleParameterInterface();

        /// return true if there is a range limit
        //  on the value
        virtual bool hasRange() const = 0;

        virtual QString minimum() const = 0;
        virtual QString maximum() const = 0;

        virtual Report validateString(const QString&) = 0;

        /// return teh actual set value as a string
        virtual QString toString() const = 0;

    private:
};

} // namespace hic

#endif // SINGLEPARAMETERINTERFACE_H 
