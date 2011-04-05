#include "CommandsItemImpl.h"
#include "Platform.h"
#include "Report.h"
#include <iostream>


namespace hic {


/**
 * @details Constructs a CommandsItemImpl object.
 */
CommandsItemImpl::CommandsItemImpl(const Platform& p)
    : ProcedureItemImpl( p )
{
}

/**
 * @details Destroys the CommandsItemImpl object.
 */
CommandsItemImpl::~CommandsItemImpl()
{
}

bool CommandsItemImpl::isValid() const
{
    return _commands.size() > 0;
}

void CommandsItemImpl::appendCommand( const Command& command )
{
    _commands.append(command);
}

const QList<Command>& CommandsItemImpl::commands() const
{
    return _commands;
}

Report CommandsItemImpl::exec() const
{
    if( _commands.size() == 0 )
        return Report();
    return platform().exec( _commands );
}

/*
void CommandsItemImpl::write(QIODevice& device)
{
    foreach ( QString cmd , _commands )
    {
        cmd += "\n";
        device.write( cmd.toStdString().c_str(), cmd.size() );
    }
}
*/

} // namespace hic
