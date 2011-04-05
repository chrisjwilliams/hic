#ifndef COMMANDSITEM_H
#define COMMANDSITEM_H


#include "ProcedureItem.h"

/**
 * @file CommandsItem.h
 */

namespace hic {
    class Platform;
    class Command;

/**
 * @class CommandsItem
 * 
 * @brief
 *   An Item to execute commands on a platform
 * @details
 * 
 */
class CommandsItem : public ProcedureItem
{
    public:
        /// CommandsItem constructor.
        CommandsItem(const Platform& platform);

        /// CommandsItem destructor.
        ~CommandsItem();

        /// add a command to the list of commands to be executed
        void appendCommand( const Command& content );

        /// convenience function for simple commands
        void appendCommand( const QString& content );

    private:
};

} // namespace hic

#endif // COMMANDSITEM_H 
