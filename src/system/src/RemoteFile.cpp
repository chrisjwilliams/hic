/*
 * Copyright (c) 2011, The University of Oxford
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the University of Oxford nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
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

