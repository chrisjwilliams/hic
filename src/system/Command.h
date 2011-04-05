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
#ifndef COMMAND_H
#define COMMAND_H

#include <QString>
#include <QSet>

/**
 * @file Command.h
 */

namespace hic {

/**
 * @class Command
 * 
 * @brief
 *    Contain information about a command to run and what to expect
 *    when running it
 * @details
 * 
 */
class Command
{
    public:
        /// Command constructor.
        Command(const QString& cmd);

        /// Command destructor.
        ~Command();

        /// returns a string with the command and all arguments for processing
        const QString& fullCommand() const { return _cmd; }

        /// return true if the exit code has an acceptable 
        //  value to indicate success
        bool isExitCodeExpected( int code ) const;

        /// add the codes codes to the acceptable codes list
        //  if this is not called a default value of 0 will be assumed
        //  to indicate success
        void setExpectedExitCodes( const QSet<int>& );
        void setExpectedExitCode( int );

    private:
        QString _cmd;
        QSet<int> _goodCodes;
};

} // namespace hic

#endif // COMMAND_H 
