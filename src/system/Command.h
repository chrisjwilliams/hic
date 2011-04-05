#ifndef COMMAND_H
#define COMMAND_H

#include <QString>
#include <QSet>

/**
 * @file Command.h
 */

namespace hic {

/**
 * @class Command
 * 
 * @brief
 *    Contain information about a command to run and what to expect
 *    when running it
 * @details
 * 
 */
class Command
{
    public:
        /// Command constructor.
        Command(const QString& cmd);

        /// Command destructor.
        ~Command();

        /// returns a string with the command and all arguments for processing
        const QString& fullCommand() const { return _cmd; }

        /// return true if the exit code has an acceptable 
        //  value to indicate success
        bool isExitCodeExpected( int code ) const;

        /// add the codes codes to the acceptable codes list
        //  if this is not called a default value of 0 will be assumed
        //  to indicate success
        void setExpectedExitCodes( const QSet<int>& );
        void setExpectedExitCode( int );

    private:
        QString _cmd;
        QSet<int> _goodCodes;
};

} // namespace hic

#endif // COMMAND_H 
