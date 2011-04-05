#include "SSH_FileTransfer.h"
#include <QProcess>
#include "system/Platform.h"
#include "system/Report.h"

namespace hic {

/**
 * @details Constructs a SSH_FileTransfer object.
 * Temporarily Uses the local machines client scp program
 * with no special handling of credentials etc.
 */
SSH_FileTransfer::SSH_FileTransfer()
    : _user("")
{
    setClient("/usr/bin/scp"); // default value
}

/**
 * @details Destroys the SSH_FileTransfer object.
 */
SSH_FileTransfer::~SSH_FileTransfer()
{
}

void SSH_FileTransfer::setUser(const QString& user)
{
    _user = user;
}

Report SSH_FileTransfer::getFile(const QString& remote_filename, const QString& local_filename )
{
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
}

Report SSH_FileTransfer::putFile(const QString& local_filename, const QString& remote_filename )
{
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
}

} // namespace hic
