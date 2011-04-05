class State
!!!146276.cpp!!!	State(in s : State)
    _groups = s._groups;
    _states = s._states;
    _name = s._name;
    _active = s._active;
!!!147300.cpp!!!	addSubState(inout s : State) : void
    _states.append(s);
