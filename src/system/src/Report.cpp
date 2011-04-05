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
#include "Report.h"
#include <QTextStream>



namespace hic {


/**
 * @details Constructs a Report object.
 */
Report::Report()
{
    _success = true;
    newCommand(""); // ensure atr least one command object exists
}

/**
 * @details Destroys the Report object.
 */
Report::~Report()
{
}

void Report::newCommand(const QString& cmd)
{
    _cmds.append(CommandReport(cmd));
}

void Report::addMessage(const QString& msg)
{
    _cmds.last().addStdOut(msg);
}

void Report::addErrorMessage(const QString& msg)
{
    if( msg != "" ) {
        _success = false;
        _error = msg;
        _cmds.last().addStdErr(msg);
    }
}

bool Report::success() const
{
    return _success;
}

Report& Report::operator+=(const Report& r)
{
    if( r._success == false )
    {
        _success = false;
        _error = r._error;
    }
    _cmds += r._cmds;

    _rv = r._rv;
    return *this;
}

void Report::dump() const
{
    foreach( const CommandReport& c, _cmds )
    {
        //if( c.command() == c.stdOut() == c.stdErr() == "" )
        //    continue;
        QTextStream s(stdout);
        s << "<command>\n"
          << c.command() << "\n"
          << "  <returnValue>\n"
          << c.getCode()
          << "  </returnValue>\n"
          << "  <stdout>\n"
          << c.stdOut()
          << "\n  </stdout>\n"
          << "  <stderr>\n"
          << c.stdErr()
          << "\n  </stderr>\n"
          << "</command>\n";
    }
}
} // namespace hic
