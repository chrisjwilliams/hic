class ProcedureItem
!!!181860.cpp!!!	exec() : Report
    Q_ASSERT( _impl.get() != 0 );
    return _impl->exec();
!!!181988.cpp!!!	isValid() : bool
    Q_ASSERT( _impl.get() != 0 );
    return _impl->isValid();
