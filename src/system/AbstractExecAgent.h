#ifndef ABSTRACTEXECAGENT_H
#define ABSTRACTEXECAGENT_H


#include "AbstractAgent.h"

/**
 * @file AbstractExecAgent.h
 */

namespace hic {
    class Command;

/**
 * @class AbstractExecAgent
 * 
 * @brief
 *   Abstract class for agents that execute commands remotely
 * @details
 * 
 */
class AbstractExecAgent : public AbstractAgent
{
    public:
        /// AbstractExecAgent constructor.
        AbstractExecAgent();

        /// AbstractExecAgent destructor.
        virtual ~AbstractExecAgent();

        /// execute the commands provided
        virtual Report exec( const QList<Command>& commands ) = 0;

    private:
};

} // namespace hic

#endif // ABSTRACTEXECAGENT_H 
