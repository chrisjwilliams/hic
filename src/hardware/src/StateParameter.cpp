#include "StateParameter.h"


namespace hic {


/**
 * @details Constructs a StateParameter object.
 */
StateParameter::StateParameter( const QString& name, const QString& doc )
    : _name(name), _doc(doc)
{
}

/**
 * @details Destroys the StateParameter object.
 */
StateParameter::~StateParameter()
{
}

void StateParameter::setRestrictedValues( const QMap<QString,QString >& values )
{
    _restrictedValues = values;
}

QList<QString> StateParameter::restrictedValues() const
{
    return _restrictedValues.keys();
}

} // namespace hic
