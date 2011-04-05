#include "LocalHostFileTransfer.h"
#include <QFile>
#include "system/Report.h"


namespace hic {


/**
 * @details Constructs a LocalHostFileTransfer object.
 */
LocalHostFileTransfer::LocalHostFileTransfer()
{
}

/**
 * @details Destroys the LocalHostFileTransfer object.
 */
LocalHostFileTransfer::~LocalHostFileTransfer()
{
}

Report LocalHostFileTransfer::putFile(const QString& local_filename, const QString& remote_filename )
{
    Report report;
    if( remote_filename != local_filename )
    {
        QFile file;
        file.setFileName(local_filename);
        file.copy(remote_filename);
    }
    return report;
}

Report LocalHostFileTransfer::getFile(const QString& remote_filename, const QString& local_filename )
{
    Report report;
    if( remote_filename != local_filename )
    {
        QFile file(remote_filename);
        if( ! file.exists() ) {
            report.addErrorMessage(QString("file ") + remote_filename + QString(" does not exist" ) );
            return report;
        }
        if( ! QFile::copy(remote_filename, local_filename) ) {
            report.addErrorMessage( QString("unable to copy file ") + remote_filename + QString(" to ") + local_filename );
            return report;
        }
    }
    return report;
}

} // namespace hic
