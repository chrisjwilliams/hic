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
