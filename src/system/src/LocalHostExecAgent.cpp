#include "LocalHostExecAgent.h"
#include <QProcess>
#include <QFile>
#include "Report.h"
#include "Command.h"


namespace hic {


/**
 * @details Constructs a LocalHostExecAgent object.
 */
LocalHostExecAgent::LocalHostExecAgent()
{
}

/**
 * @details Destroys the LocalHostExecAgent object.
 */
LocalHostExecAgent::~LocalHostExecAgent()
{
}

Report LocalHostExecAgent::exec( const QList<Command>& commands )
{
    Report report;
    QProcess proc;
    foreach ( const Command& command , commands )
    {
        report.newCommand( command.fullCommand() );
        proc.start( command.fullCommand() );
        if (!proc.waitForStarted())
        {
            report.addErrorMessage(
                    QString("Platform::exec: unable to start : QProcess::ProcessError=%1")
                    .arg(proc.error()));
            break;
        }
        // transfer data into the report
        proc.waitForFinished(-1);
        report.setExitCode( proc.exitCode() );
        report.addMessage( proc.readAllStandardOutput() );
        report.addErrorMessage( proc.readAllStandardError() );
        if( ! command.isExitCodeExpected(proc.exitCode()) )
        {
            report.addErrorMessage(QString("failed with exit code %1").arg( proc.exitCode() ) );
            break;
        }
    }
    return report;
}

} // namespace hic
