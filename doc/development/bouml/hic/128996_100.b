class Report
!!!183780.cpp!!!	Report()
    _success = true;
    newCommand(""); // ensure atr least one command object exists
!!!184036.cpp!!!	newCommand(in cmd : QString) : void
    _cmds.append(CommandReport(cmd));
!!!185060.cpp!!!	addMessage(in msg : QString) : void
    _cmds.last().addStdOut(msg);
!!!184804.cpp!!!	addErrorMessage(in msg : QString) : void
    if( msg != "" ) {
        _success = false;
        _error = msg;
        _cmds.last().addStdErr(msg);
    }
!!!184164.cpp!!!	success() : bool
    return _success;
!!!185188.cpp!!!	operator +=(in r : Report) : Report
    if( r._success == false )
    {
        _success = false;
        _error = r._error;
    }
    _cmds += r._cmds;

    _rv = r._rv;
    return *this;
!!!185316.cpp!!!	dump() : void
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
