#include "SingleParameterInterface.h"


namespace hic {


/**
 * @details Constructs a SingleParameterInterface object.
 */
SingleParameterInterface::SingleParameterInterface( const QString& name, const QString& doc )
    : ParameterQObject(ParameterQObject::Types::SingleValue,name,doc)
{
}

/**
 * @details Destroys the SingleParameterInterface object.
 */
SingleParameterInterface::~SingleParameterInterface()
{
}

} // namespace hic
