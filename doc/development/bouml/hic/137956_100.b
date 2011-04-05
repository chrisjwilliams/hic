class CommandsItemImpl
!!!176612.cpp!!!	isValid() : bool
    return _commands.size() > 0;
!!!176356.cpp!!!	appendCommand(in command : Command) : void
    _commands.append(command);
!!!176484.cpp!!!	commands() : QList<Command>
    return _commands;
!!!176740.cpp!!!	exec() : Report
    if( _commands.size() == 0 )
        return Report();
    return platform().exec( _commands );
