#ifndef SSH_EXECAGENT_H
#define SSH_EXECAGENT_H


#include "AbstractExecAgent.h"

/**
 * @file SSH_ExecAgent.h
 */

namespace hic {
    class Command;

/**
 * @class SSH_ExecAgent
 * 
 * @brief
 *   Wrapper for executing on a remote host via SSH
 * @details
 * 
 */
class SSH_ExecAgent : public AbstractExecAgent
{
    public:
        /// SSH_ExecAgent constructor.
        SSH_ExecAgent();

        /// SSH_ExecAgent destructor.
        ~SSH_ExecAgent();

        /// execute a series of commands
        virtual Report exec( const QList<Command>& commands );

        /// set the user to connect with
        void setUser(const QString& user);

    private:
        QString _user;
        QString _ssh;
        QString _sshExec;
};

} // namespace hic

#endif // SSH_EXECAGENT_H 
