#include "LocalHost.h"
#include "system/LocalHostFileTransfer.h"
#include "system/LocalHostExecAgent.h"

namespace hic {


/**
 * @details Constructs a LocalHost object.
 */
LocalHost::LocalHost()
    : Platform("localhost")
{
    setFileTransferAgent( new LocalHostFileTransfer );
    setExecAgent( new LocalHostExecAgent );
}

/**
 * @details Destroys the LocalHost object.
 */
LocalHost::~LocalHost()
{
}

} // namespace hic
