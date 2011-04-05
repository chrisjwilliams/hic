class RCU_Filter
!!!168420.cpp!!!	RCU_Filter(in type : QString)
    setType(type);
!!!169316.cpp!!!	options() : QList<QString>
    static QList<QString> _options;
    _options << "UNSET" << "LBL 10MHz HPF" 
             << "LBL 30MHz HPF" << "LBH 10MHz HPF" 
             << "LBH 30MHz HPF" << "HB 110-190MHz" 
             << "HB 170-230MHz" << "HB 210-270MHz";
    return _options;
!!!169188.cpp!!!	setType(in type : QString) : void
    int index = options().indexOf(type);
    if( index >= 0 )
        _type = index;
!!!168804.cpp!!!	name() : QString
    return options()[_type];
!!!168676.cpp!!!	filterId() : int
    return _type;
!!!168932.cpp!!!	operator ==(in f : RCU_Filter) : bool
    return _type == f._type;
!!!169060.cpp!!!	operator !=(in f : RCU_Filter) : bool
    return _type != f._type;
