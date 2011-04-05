#include "StateController.h"
#include "AbstractGenerator.h"
#include "system/Procedure.h"
#include "system/Report.h"
#include <iostream>


namespace hic {

/**
 * @details Constructs a StateController object.
 */
StateController::StateController( QObject* parent )
    : QObject(parent)
{
}

/**
 * @details Destroys the StateController object.
 */
StateController::~StateController()
{
    foreach( AbstractGenerator* gen, _generators ) {
        delete gen;
    }
}

void StateController::addGenerator(AbstractGenerator* generator)
{
    _generators.append(generator);
}

Report StateController::setState(const State& state)
{
    Procedure proc;
    // shutdown the previous state
    foreach( const AbstractGenerator* generator, _generators )
    {
        proc.appendProcedure( generator->stop() );
    }
    // setup the new state
    foreach( const AbstractGenerator* generator, _generators )
    {
        proc.appendProcedure( generator->setState( state ) );
    }
    connect( &proc, SIGNAL( status(const QString&) ),
             this, SLOT( _status(const QString&)) );
    Report r = proc.exec();
    emit statusReport(r);
    return r;
}

void StateController::_status(const QString& msg) 
{
    if( msg != "" )
        emit status(msg);
}

} // namespace hic
