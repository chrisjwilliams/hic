class LCU_Platform
!!!160740.cpp!!!	LCU_Platform()
    //setFileTransferAgent( new LocalHostFileTransfer );
    //setExecAgent( new LocalHostExecAgent );
    setFileTransferAgent( new SSH_FileTransfer );
    setExecAgent( new SSH_ExecAgent );
!!!160996.cpp!!!	setHost(in host : boost::shared_ptr<SingleParameter<QString> >) : void
    _host = host;
    hostUpdated();
    connect( _host.get(), SIGNAL( updated() ), this, SLOT ( hostUpdated() ) );
!!!161124.cpp!!!	hostUpdated() : void
    std::cout << "hostname = " << _host->toString().toStdString() << std::endl;
    setHostName( _host->toString() );
