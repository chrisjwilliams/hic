class LocalHostFileTransfer
!!!179172.cpp!!!	putFile(in local_filename : QString, in remote_filename : QString) : Report
    Report report;
    if( remote_filename != local_filename )
    {
        QFile file;
        file.setFileName(local_filename);
        file.copy(remote_filename);
    }
    return report;
!!!179044.cpp!!!	getFile(in remote_filename : QString, in local_filename : QString) : Report
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
