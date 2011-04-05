#ifndef REMOTEFILE_H
#define REMOTEFILE_H


#include <QFile>
#include <QTemporaryFile>
#include "system/Platform.h"

/**
 * @file RemoteFile.h
 */

namespace hic {

/**
 * @class RemoteFile
 * 
 * @brief
 * 
 * @details
 * 
 */
class RemoteFile : public QFile
{
    public:
        /// RemoteFile constructor.
        RemoteFile(const Platform& platform);

        /// setFileName
        void setFileName( const QString& name );

        /// open a file for writing
        bool open( OpenMode mode );

        /// close the file
        void close();

        /// RemoteFile destructor.
        ~RemoteFile();

    private:
        QString _temporaryFileName() const;

    private:
        bool            _write;
        QString         _filename;
        Platform        _platform;
        QTemporaryFile  _localFile;
};

} // namespace hic

#endif // REMOTEFILE_H 
