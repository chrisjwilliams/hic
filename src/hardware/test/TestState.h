#ifndef TESTSTATE_H
#define TESTSTATE_H


#include "hardware/State.h"

/**
 * @file TestState.h
 */

namespace hic {

/**
 * @class TestState
 * 
 * @brief
 *    An implementation of the State object interface for testing
 * @details
 * 
 */
class TestState : public State
{
    public:
        /// TestState constructor.
        TestState();

        /// TestState destructor.
        ~TestState();

        virtual TestState* clone() const;

    private:
};

} // namespace hic

#endif // TESTSTATE_H 
