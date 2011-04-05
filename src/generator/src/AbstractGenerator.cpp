#include "AbstractGenerator.h"
#include "system/Procedure.h"
#include "system/LocalHost.h"


namespace hic {


/**
 * @details Constructs a AbstractGenerator object.
 */
AbstractGenerator::AbstractGenerator( )
{
}

/**
 * @details Destroys the AbstractGenerator object.
 */
AbstractGenerator::~AbstractGenerator()
{
}

Procedure AbstractGenerator::stop() const
{
    // defualt to returna an empty procedure
    Procedure p;
    return p;
}

LocalHost AbstractGenerator::localhost() const
{
    static LocalHost _localhost;
    return _localhost;
}

} // namespace hic
