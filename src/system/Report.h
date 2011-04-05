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
#ifndef REPORT_H
#define REPORT_H

#include <QString>
#include <QList>
#include "CommandReport.h"

/**
 * @file Report.h
 */

namespace hic {

/**
 * @class Report
 * 
 * @brief
 *    Summary of an execution, including error messages etc.
 * @details
 * 
 */
class Report
{
    public:
        /// Report constructor.
        Report();

        /// Report destructor.
        ~Report();

        /// set all subsequent methods to refer to the
        //  given command
        void newCommand(const QString& cmd);

        /// returns true if successful
        bool success() const;
        void setSuccess(bool val) { _success = val; };

        /// returns the return value of the last command to fail
        int exitCode() const { return _rv; };

        /// sets the exit code
        void setExitCode(int rv) { _rv = rv; };

        /// any output produced from execution
        const QString& commandOutput() const;

        void addErrorMessage(const QString&);

        const QString& errorMessage() const { return _error; };

        void addMessage(const QString&);

        Report& operator+=(const Report&);

        /// dump to std output an XML rendition of the report
        void dump() const;

    private:
        QList<CommandReport> _cmds;
        bool _success;
        int _rv;
        QString _error;
};

} // namespace hic

#endif // REPORT_H 
