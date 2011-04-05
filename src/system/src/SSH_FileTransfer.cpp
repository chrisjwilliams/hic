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
