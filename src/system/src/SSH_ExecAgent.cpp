#include "SSH_ExecAgent.h"
#include <QProcess>
#include <QList>
#include <QDebug>
#include "Report.h"
#include "system/Command.h"


namespace hic {


/**
 * @details Constructs a SSH_ExecAgent object.
 */
SSH_ExecAgent::SSH_ExecAgent()
   : _user("")
{
    _ssh ="/usr/bin/ssh";
}

/**
 * @details Destroys the SSH_ExecAgent object.
 */
SSH_ExecAgent::~SSH_ExecAgent()
{
}

void SSH_ExecAgent::setUser(const QString& user)
{
    _user = user;
}

Report SSH_ExecAgent::exec( const QList<Command>& commands )
{
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
}

} // namespace hic
