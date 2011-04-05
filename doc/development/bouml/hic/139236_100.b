class SSH_FileTransfer
!!!185956.cpp!!!	SSH_FileTransfer()
    setClient("/usr/bin/scp"); // default value
!!!186340.cpp!!!	setUser(in user : QString) : void
    _user = user;
!!!186468.cpp!!!	getFile(in remote_filename : QString, in local_filename : QString) : Report
    Report report;
    QProcess p;
    QList<QString> arguments;
    if( _user != "" ) {
        arguments << "-l" << _user;
    }
    arguments << platform()->name() + ":" + remote_filename << local_filename;
    p.start( _scp, arguments );
    if( p.exitCode() != 0 )
    {
        report.addErrorMessage(QString("failed with exit code %1").arg( p.exitCode() ) );
    }
    return report;
!!!186596.cpp!!!	putFile(in local_filename : QString, in remote_filename : QString) : Report
    Report report;
    QProcess p;
    QList<QString> arguments;
                   arguments << local_filename << platform()->name() + ":" + remote_filename;
    //r.addMessage("executing command" + _scp + arguments );
    p.start( _scp, arguments );
    if( p.exitCode() != 0 )
    {
        report.addErrorMessage(QString("failed with exit code %1").arg( p.exitCode() ) );
    }
    return report;
