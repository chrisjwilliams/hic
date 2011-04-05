#include "MultiRangeParameterInterface.h"


namespace hic {


/**
 * @details Constructs a MultiRangeParameterInterface object.
 */
MultiRangeParameterInterface::MultiRangeParameterInterface( const QString& name, const QString& doc )
    : ParameterQObject( ParameterQObject::Types::MultiRange, name, doc ),
              _rangeSeparator(","), _rangeCont("..") 
{
    
}

/**
 * @details Destroys the MultiRangeParameterInterface object.
 */
MultiRangeParameterInterface::~MultiRangeParameterInterface()
{
}

} // namespace hic
