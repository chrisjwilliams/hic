class SelectionParameterInterface
!!!142564.cpp!!!	allowableValues() : QList<QString>
    return _allowable;
!!!143076.cpp!!!	_setFromString(in s : QString) : Report
    Report r;
    if( ! _allowable.contains(s) ) {
        r.addErrorMessage(s + " is not a valid value for parameter : " 
                            + name() );
    }
    else {
        setFromIndex(_allowable.indexOf(s));
    }
    return r;
!!!142948.cpp!!!	setFromIndex(in index : int) : void
    if( ( index > -1 ) && ( index < _allowable.size( )) )
    {
//    std::cout << this << " SelectionParameterInterface::setFromIndex : index = " << index <<std::endl;
        _currentIndex = index;
        emit updatedSelection();
    }
