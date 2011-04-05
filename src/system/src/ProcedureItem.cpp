#include "ProcedureItem.h"
#include "ProcedureItemImpl.h"
#include "Report.h"
#include <iostream>

namespace hic {

/**
 * @details Constructs a ProcedureItem object.
 *          Inheriting class should always create the appropriate
 *          Implemantion object in the constructor.
 *
 *          the platform is passed to allow instantiation of ProcedureItemImpl
 *          objects
 */
ProcedureItem::ProcedureItem( const Platform& /*platform*/ )
{
}

/**
 * @details Destroys the ProcedureItem object.
 */
ProcedureItem::~ProcedureItem()
{
}

/**
 * @details Execute the procedure
 */
Report ProcedureItem::exec() const
{
    Q_ASSERT( _impl.get() != 0 );
    return _impl->exec();
}

bool ProcedureItem::isValid() const
{
    Q_ASSERT( _impl.get() != 0 );
    return _impl->isValid();
}

} // namespace hic
