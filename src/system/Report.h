#ifndef REPORT_H
#define REPORT_H

#include <QString>
#include <QList>
#include "CommandReport.h"

/**
 * @file Report.h
 */

namespace hic {

/**
 * @class Report
 * 
 * @brief
 *    Summary of an execution, including error messages etc.
 * @details
 * 
 */
class Report
{
    public:
        /// Report constructor.
        Report();

        /// Report destructor.
        ~Report();

        /// set all subsequent methods to refer to the
        //  given command
        void newCommand(const QString& cmd);

        /// returns true if successful
        bool success() const;
        void setSuccess(bool val) { _success = val; };

        /// returns the return value of the last command to fail
        int exitCode() const { return _rv; };

        /// sets the exit code
        void setExitCode(int rv) { _rv = rv; };

        /// any output produced from execution
        const QString& commandOutput() const;

        void addErrorMessage(const QString&);

        const QString& errorMessage() const { return _error; };

        void addMessage(const QString&);

        Report& operator+=(const Report&);

        /// dump to std output an XML rendition of the report
        void dump() const;

    private:
        QList<CommandReport> _cmds;
        bool _success;
        int _rv;
        QString _error;
};

} // namespace hic

#endif // REPORT_H 
