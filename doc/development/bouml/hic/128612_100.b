class LocalHost
!!!178148.cpp!!!	LocalHost()
    setFileTransferAgent( new LocalHostFileTransfer );
    setExecAgent( new LocalHostExecAgent );
