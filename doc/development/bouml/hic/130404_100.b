class ParameterQObject
!!!137700.cpp!!!	setFromString(in s : QString) : Report
    Report r;
    try {
        // call the specialisation
        r += _setFromString(s);
        if( r.success() )
            emit updatedSelection();
    }
    catch( const Report& err ) {
        r += err;
    }
    catch( const QString& err ) {
        r.addErrorMessage(err);
    }
    return r;
!!!138212.cpp!!!	verbose(in msg : QString, in level : int = 1) : void
    if( _verbose >= level ) {
        std::cout << "Parameter::" << name().toStdString() 
                  << ": " << this << ":" 
                  << msg.toStdString() << std::endl;
    }
