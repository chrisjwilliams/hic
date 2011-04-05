#include "TestProcedureItem.h"
#include "TestProcedureItemImpl.h"


namespace hic {


/**
 * @details Constructs a TestProcedureItem object.
 */
TestProcedureItem::TestProcedureItem(const Platform& p)
    : ProcedureItem(p)
{
    _impl.reset( new TestProcedureItemImpl( p ) );
}

/**
 * @details Destroys the TestProcedureItem object.
 */
TestProcedureItem::~TestProcedureItem()
{
}

} // namespace hic
