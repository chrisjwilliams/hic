#include "ParameterGroup.h"



namespace hic {


/**
 * @details Constructs a ParameterGroup object.
 */
ParameterGroup::ParameterGroup(const QString& name)
    : _name(name), _deactivatible(false)
{
    _active = true;
}

/**
 * @details Destroys the ParameterGroup object.
 */
ParameterGroup::~ParameterGroup()
{
}

const QString& ParameterGroup::name() const
{
    return _name;
}

bool ParameterGroup::canDeactivate() const
{
    return _deactivatible;
}

void ParameterGroup::enableDeactivation()
{
    _deactivatible = true;
}

void ParameterGroup::addParameter(const boost::shared_ptr<ParameterQObject>&  param)
{
    _params.append(param);
}

const QList<boost::shared_ptr<ParameterQObject> >& ParameterGroup::parameters() const
{
    return _params;
}

} // namespace hic
