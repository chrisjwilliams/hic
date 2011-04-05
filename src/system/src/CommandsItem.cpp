#include "CommandsItem.h"
#include "CommandsItemImpl.h"
#include "Platform.h"
#include "Command.h"

namespace hic {


/**
 * @details Constructs a CommandsItem object.
 */
CommandsItem::CommandsItem(const Platform& platform)
    : ProcedureItem(platform)
{
    _impl.reset( new CommandsItemImpl( platform ) );
    setStatusMessage( QString("executing commands on platform %1")
                            .arg(platform.name()) ); // default status message
}

/**
 * @details Destroys the CommandsItem object.
 */
CommandsItem::~CommandsItem()
{
}

void CommandsItem::appendCommand( const QString& com )
{
    Command c(com);
    c.setExpectedExitCode(0);
    appendCommand( c );
}

void CommandsItem::appendCommand( const Command& com )
{
    static_cast<CommandsItemImpl*>(_impl.get())->appendCommand(com);
}
} // namespace hic
