class RemoteFile
!!!183524.cpp!!!	~RemoteFile()
    close();
!!!183396.cpp!!!	close() : void
    QFile::close();
    if( _write ) {
        _localFile.flush();
        _platform.putFile( _localFile.fileName() , _filename );
        _localFile.close();
    }
    else {
        if( fileName() == _temporaryFileName() )
            remove();
    }
    _write =false;
!!!183140.cpp!!!	setFileName(in name : QString) : void
    _filename = name;
!!!183652.cpp!!!	_temporaryFileName() : QString
    return QDir::tempPath() + "/hic_remoteFile_"; // + _filename;
