class CommandsItem
!!!175588.cpp!!!	CommandsItem(in platform : Platform)
    _impl.reset( new CommandsItemImpl( platform ) );
    setStatusMessage( QString("executing commands on platform %1")
                            .arg(platform.name()) ); // default status message
!!!175972.cpp!!!	appendCommand(in com : QString) : void
    Command c(com);
    c.setExpectedExitCode(0);
    appendCommand( c );
!!!175844.cpp!!!	appendCommand(in com : Command) : void
    static_cast<CommandsItemImpl*>(_impl.get())->appendCommand(com);
