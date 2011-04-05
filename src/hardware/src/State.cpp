#include "State.h"


namespace hic {


/**
 * @details Constructs a State object.
 */
State::State(bool canDeactivate, QObject* parent)
    : QObject(parent), _active(true), _canDeactivate(canDeactivate)
{
}

/**
 * @details Destroys the State object.
 */
State::~State()
{
}

State::State(const State& s)
    : QObject(s.parent())
{
    _groups = s._groups;
    _states = s._states;
    _name = s._name;
    _active = s._active;
}

void State::addSubState(State* s)
{
    _states.append(s);
}



} // namespace hic
