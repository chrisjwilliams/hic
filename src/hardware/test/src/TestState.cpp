#include "TestState.h"


namespace hic {


/**
 * @details Constructs a TestState object.
 */
TestState::TestState()
    : State()
{
}

/**
 * @details Destroys the TestState object.
 */
TestState::~TestState()
{
}

TestState* TestState::clone() const
{
    return new TestState( *this );
}
} // namespace hic
