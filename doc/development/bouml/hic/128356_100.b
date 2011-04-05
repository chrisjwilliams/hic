class Procedure
!!!180836.cpp!!!	Procedure(in procedure : Procedure)
    _procs = procedure._procs;
!!!180964.cpp!!!	appendProcedure(in procedure : ProcedureItem) : void
    if( procedure.isValid() )
        _procs.append(procedure);
!!!181092.cpp!!!	appendProcedure(in procedure : Procedure) : void
    foreach( const ProcedureItem& item, procedure._procs )
    {
        appendProcedure(item);
    }
!!!181220.cpp!!!	exec() : Report
    Report report;
    foreach( const ProcedureItem& p, _procs )
    {
        emit status( p.statusMessage() );
        report += p.exec();
        if( ! report.success() )
            break;
    }
    return report;
!!!181348.cpp!!!	isValid() : bool
    bool rv = false;
    foreach( const ProcedureItem& p, _procs )
    {
        rv |= p.isValid();
    }
    return rv;
