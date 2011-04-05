#include "SelectionParameter.h"
#include "ParameterQObject.h"

namespace hic {


/**
 * @details Constructs a SelectionParameter object.
 */
SelectionParameter::SelectionParameter()
    : Parameter()
{
}

/**
 * @details Destroys the SelectionParameter object.
 */
SelectionParameter::~SelectionParameter()
{
}

const QList<QString>& SelectionParameter::allowableValues() const
{
    return _allowable;
}
} // namespace hic
