#ifndef PARAMETER_H
#define PARAMETER_H

#include "ParameterQObject.h"

/**
 * @file Parameter.h
 */

namespace hic {

/**
 * @class Parameter
 * 
 * @brief
 *   Base class for Parameters
 * @details
 *   
 */

template<typename T>
class Parameter : public ParameterQObject
{

    public:
        /// Parameter constructor.
        Parameter(typeT type, const QString& name, const QString doc)
            : ParameterQObject(type,name,doc)
        {
        }

        /// Parameter destructor.
        virtual ~Parameter() {};

        virtual void set(const T& v) { _value = v; emit updated(); };
        virtual const T& value() const { return _value; };

    private:
        T  _value;
        
};

} // namespace hic

#endif // PARAMETER_H 
