#include "RemoteFile.h"
#include <QDir>
#include "Report.h"

namespace hic {


/**
 * @details Constructs a RemoteFile object.
 */
RemoteFile::RemoteFile(const Platform& platform)
    : _platform(platform)
{
}

/**
 * @details Destroys the RemoteFile object.
 */
RemoteFile::~RemoteFile()
{
    close();
}

bool RemoteFile::open( QIODevice::OpenMode mode )
{
    if( _filename == "" )
            throw( QString("RemoteFile: filename not specified") );
    _write = false;
    switch ( mode ) {
        case QIODevice::WriteOnly:
            _localFile.open();
            _write = true;
            QFile::setFileName( _localFile.fileName() );
            return QFile::open(QIODevice::WriteOnly);
            break;
        case QIODevice::ReadOnly:
            throw( QString("RemoteFile: openMode not supported for file ") + _filename );
            /*
            //_localFile.open();
            try {
                _platform.getFile( _filename, _temporaryFileName() );
            }
            catch( const QString& s )
            {
                throw( QString("RemoteFile: unable to open remote file to Read \"") + _filename + "\" : " + s );
            }
            QFile::setFileName( _temporaryFileName() );
            return QFile::open(QIODevice::ReadOnly);
            */
            break;
        default:
            throw( QString("RemoteFile: openMode not supported for file ") + _filename );
    }
    return true;
}

void RemoteFile::close()
{
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
}

void RemoteFile::setFileName( const QString& name )
{
    _filename = name;
}

QString RemoteFile::_temporaryFileName() const
{
    return QDir::tempPath() + "/hic_remoteFile_"; // + _filename;
}

} // namespace hic

