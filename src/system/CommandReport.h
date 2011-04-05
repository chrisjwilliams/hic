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
#ifndef COMMANDREPORT_H
#define COMMANDREPORT_H

#include <QString>

/**
 * @file CommandReport.h
 */

namespace hic {

/**
 * @class CommandReport
 * 
 * @brief
 *   class to contain reporting data of a single command execution
 * @details
 * 
 */
class CommandReport
{
    public:
        /// CommandReport constructor.
        CommandReport(const QString& command);

        /// CommandReport destructor.
        ~CommandReport();

        /// retunrs the command name
        const QString& command() const { return _cmd; };

        /// add a message to the stdout section
        void addStdOut(const QString&);

        /// add a message to the stderr section
        void addStdErr(const QString&);

        /// set the error code of completion
        void setCode(int returnValue ) { _code = returnValue; };
        int getCode() const { return _code; };

        /// the stdout messages
        const QString& stdOut() const { return _stdout; };

        /// the stderr messages
        const QString& stdErr() const { return _stderr; };

    private:
        int _code;
        QString _cmd;
        QString _stdout;
        QString _stderr;
};

} // namespace hic

#endif // COMMANDREPORT_H 
