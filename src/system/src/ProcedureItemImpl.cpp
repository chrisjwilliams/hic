#include "ProcedureItemImpl.h"
#include "ProcedureItem.h"



namespace hic {


/**
 * @details Constructs a ProcedureItemImpl object.
 */
ProcedureItemImpl::ProcedureItemImpl(const Platform& platform)
    : _platform(platform)
{
}

/**
 * @details Destroys the ProcedureItemImpl object.
 */
ProcedureItemImpl::~ProcedureItemImpl()
{
}

const Platform& ProcedureItemImpl::platform() const
{
    return _platform;
    //return _api->platform();
}
} // namespace hic
