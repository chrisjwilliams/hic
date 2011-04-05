class ParameterGroup
!!!135780.cpp!!!	ParameterGroup(in name : QString)
    _active = true;
!!!136036.cpp!!!	name() : QString
    return _name;
!!!136292.cpp!!!	canDeactivate() : bool
    return _deactivatible;
!!!136420.cpp!!!	enableDeactivation() : void
    _deactivatible = true;
!!!136804.cpp!!!	addParameter(in param : boost::shared_ptr<ParameterQObject>) : void
    _params.append(param);
!!!136164.cpp!!!	parameters() : QList<boost::shared_ptr<ParameterQObject> >
    return _params;
