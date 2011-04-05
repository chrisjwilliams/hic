class SSH_ExecAgent
!!!185444.cpp!!!	SSH_ExecAgent()
    _ssh ="/usr/bin/ssh";
!!!185828.cpp!!!	setUser(in user : QString) : void
    _user = user;
!!!185700.cpp!!!	exec(in commands : QList<Command>) : Report
    Report report;
    QProcess proc;
    foreach ( const Command& command , commands )
    {
        report.newCommand( command.fullCommand() );
        QList<QString> args;
        if( _user != "" ) {
            args << "-l" << _user;
        }
        args << "-n" << platform()->name() << command.fullCommand();

        proc.start( _ssh, args );
        if (!proc.waitForStarted())
        {
            report.addErrorMessage(
                    QString("Platform::SSH_ExecAgent::exec: unable to start : QProcess::ProcessError=%1")
                    .arg(proc.error()));
            break;
        }
        proc.waitForFinished(-1);
        report.setExitCode( proc.exitCode() );
        report.addMessage( proc.readAllStandardOutput() );
        report.addErrorMessage( proc.readAllStandardError() );
        if( ! command.isExitCodeExpected(proc.exitCode()) )
        {
            report.addErrorMessage(QString("failed with exit code %1").
                    arg( proc.exitCode() ) + "\n" + report.errorMessage() );
            break;
        }
    }
    return report;
