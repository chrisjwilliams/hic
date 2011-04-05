#include "BeamDirection.h"


namespace hic {

/**
 * @details Constructs a BeamDirection object.
 */
BeamDirection::BeamDirection()
    : _type("undefined")
{
}

BeamDirection::BeamDirection( float x, float y, const QString& type )
    : _type(type), _x(x), _y(y)
{
}
/**
 * @details Destroys the BeamDirection object.
 */
BeamDirection::~BeamDirection()
{
}

bool BeamDirection::isValid() const
{
    return _type != "undefined";
}

QList<QString> BeamDirection::types()
{
    QList<QString> list;
    list << "J2000" << "AZEL" << "LOFAR_LMN" << "SKYSCAN";
    return list;
}

} // namespace hic
