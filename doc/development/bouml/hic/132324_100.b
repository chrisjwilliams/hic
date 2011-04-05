class Convertor
!!!190308.cpp!!!	fromString(in s : QString) : T
 
    bool ok; 
    int r=s.toInt(&ok); 
    if( ! ok )
        throw QString("Cannot convert " + s + " to an integer");
    return r;
!!!190436.cpp!!!	fromString(in s : QString) : T
 
    bool ok; 
    int r=s.toUInt(&ok); 
    if( ! ok )
        throw QString("Cannot convert " + s + " to an integer");
    return r;
!!!190564.cpp!!!	fromString(in s : QString) : T
    bool ok; 
    int r=s.toFloat(&ok); 
    if( ! ok )
        throw QString("Cannot convert " + s + " to a float");
    return r;
!!!190692.cpp!!!	fromString(in s : QString) : T
    bool ok; 
    int r=s.toDouble(&ok); 
    if( ! ok )
        throw QString("Cannot convert " + s + " to a double");
    return r;
!!!190820.cpp!!!	fromString(in s : QString) : T
 
    return s; 
