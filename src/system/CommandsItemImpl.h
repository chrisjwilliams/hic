#ifndef COMMANDSITEMIMPL_H
#define COMMANDSITEMIMPL_H

#include <QList>
#include "ProcedureItemImpl.h"
#include "Command.h"

/**
 * @file CommandsItemImpl.h
 */

namespace hic {
    class Report;

/**
 * @class CommandsItemImpl
 * 
 * @brief
 *    Allows the speicification of a list of commands to be executed
 * @details
 * 
 */
class CommandsItemImpl : public ProcedureItemImpl
{
    public:
        /// CommandsItemImpl constructor.
        CommandsItemImpl(const Platform& );

        /// CommandsItemImpl destructor.
        ~CommandsItemImpl();

        /// add a command to be executed
        void appendCommand(const Command& cmd);

        /// returns a list of all commands
        const QList<Command>& commands() const;

        /// returns true if there are any commands available
        virtual bool isValid() const;

        /// execute the commands
        virtual Report exec() const;

    protected:
        /// write out the list of commands to the device
        //void write(QIODevice& device);

    private:
        QList<Command> _commands;
};

} // namespace hic

#endif // COMMANDSITEMIMPL_H 
