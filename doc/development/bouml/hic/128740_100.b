class StateController
!!!128996.cpp!!!	~StateController()
    foreach( AbstractGenerator* gen, _generators ) {
        delete gen;
    }
!!!129252.cpp!!!	addGenerator(inout generator : AbstractGenerator) : void
    _generators.append(generator);
!!!129124.cpp!!!	setState(in state : State) : Report
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
!!!129636.cpp!!!	_status(in msg : QString) : void
    if( msg != "" )
        emit status(msg);
