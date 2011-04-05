class Platform
!!!179428.cpp!!!	Platform(in p : Platform)
    _execAgent = p._execAgent;
    _fileTransferAgent = p._fileTransferAgent;
    _name = p.name();
!!!180452.cpp!!!	setExecAgent(inout agent : AbstractExecAgent) : void
    Q_ASSERT( agent != 0 );
    _execAgent.reset(agent);
    _execAgent->setPlatform(this);
!!!180324.cpp!!!	setFileTransferAgent(inout agent : AbstractFileTransfer) : void
    Q_ASSERT( agent != 0 );
    _fileTransferAgent.reset(agent);
    _fileTransferAgent->setPlatform(this);
!!!179940.cpp!!!	exec(in commands : QList<Command>) : Report
    Q_ASSERT( _execAgent != 0 );
    return _execAgent->exec(commands);
!!!180068.cpp!!!	getFile(in remote_filename : QString, in local_filename : QString) : Report
    Q_ASSERT( _fileTransferAgent != 0 );
    return _fileTransferAgent->getFile(local_filename, remote_filename);
!!!180196.cpp!!!	putFile(in local_filename : QString, in remote_filename : QString) : Report
    Q_ASSERT( _fileTransferAgent != 0 );
    return _fileTransferAgent->putFile(local_filename, remote_filename);
