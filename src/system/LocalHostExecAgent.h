#ifndef LOCALHOSTEXECAGENT_H
#define LOCALHOSTEXECAGENT_H


#include "AbstractExecAgent.h"

/**
 * @file LocalHostExecAgent.h
 */

namespace hic {

/**
 * @class LocalHostExecAgent
 * 
 * @brief
 * 
 * @details
 * 
 */
class LocalHostExecAgent : public AbstractExecAgent
{
    public:
        /// LocalHostExecAgent constructor.
        LocalHostExecAgent();

        /// LocalHostExecAgent destructor.
        ~LocalHostExecAgent();

        virtual Report exec( const QList<Command>& commands );

    private:
};

} // namespace hic

#endif // LOCALHOSTEXECAGENT_H 
