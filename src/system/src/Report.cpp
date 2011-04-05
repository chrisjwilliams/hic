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
