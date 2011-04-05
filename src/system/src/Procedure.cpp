#include "Procedure.h"
#include <QIODevice>
#include <iostream>

#include "Report.h"


namespace hic {

/**
 * @details Constructs a Procedure object.
 */
Procedure::Procedure( QObject* parent )
    : QObject(parent)
{
}

/**
 * @details Destroys the Procedure object.
 */
Procedure::~Procedure()
{
}

Procedure::Procedure( const Procedure& procedure )
    : QObject(0)
{
    _procs = procedure._procs;
}

void Procedure::appendProcedure( const ProcedureItem& procedure )
{
    if( procedure.isValid() )
        _procs.append(procedure);
}

void Procedure::appendProcedure( const Procedure& procedure )
{
    foreach( const ProcedureItem& item, procedure._procs )
    {
        appendProcedure(item);
    }
}

Report Procedure::exec() 
{
    Report report;
    foreach( const ProcedureItem& p, _procs )
    {
        emit status( p.statusMessage() );
        report += p.exec();
        if( ! report.success() )
            break;
    }
    return report;
}

bool Procedure::isValid() const
{
    bool rv = false;
    foreach( const ProcedureItem& p, _procs )
    {
        rv |= p.isValid();
    }
    return rv;
}


} // namespace hic
