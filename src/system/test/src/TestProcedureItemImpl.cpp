#include "TestProcedureItemImpl.h"
#include "system/Report.h"

namespace hic {


/**
 * @details Constructs a TestProcedureItemImpl object.
 */
TestProcedureItemImpl::TestProcedureItemImpl(const Platform&  p)
    : ProcedureItemImpl(p), _isValid(true)
{
}

/**
 * @details Destroys the TestProcedureItemImpl object.
 */
TestProcedureItemImpl::~TestProcedureItemImpl()
{
}

bool TestProcedureItemImpl::isValid() const
{
    return  _isValid;
}

Report TestProcedureItemImpl::exec() const
{
    Report r;
    return r;
}

} // namespace hic
