#ifndef COMMANDREPORT_H
#define COMMANDREPORT_H

#include <QString>

/**
 * @file CommandReport.h
 */

namespace hic {

/**
 * @class CommandReport
 * 
 * @brief
 *   class to contain reporting data of a single command execution
 * @details
 * 
 */
class CommandReport
{
    public:
        /// CommandReport constructor.
        CommandReport(const QString& command);

        /// CommandReport destructor.
        ~CommandReport();

        /// retunrs the command name
        const QString& command() const { return _cmd; };

        /// add a message to the stdout section
        void addStdOut(const QString&);

        /// add a message to the stderr section
        void addStdErr(const QString&);

        /// set the error code of completion
        void setCode(int returnValue ) { _code = returnValue; };
        int getCode() const { return _code; };

        /// the stdout messages
        const QString& stdOut() const { return _stdout; };

        /// the stderr messages
        const QString& stdErr() const { return _stderr; };

    private:
        int _code;
        QString _cmd;
        QString _stdout;
        QString _stderr;
};

} // namespace hic

#endif // COMMANDREPORT_H 
