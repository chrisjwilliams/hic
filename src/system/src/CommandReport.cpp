#include "CommandReport.h"


namespace hic {


/**
 * @details Constructs a CommandReport object.
 */
CommandReport::CommandReport(const QString& command)
    : _code(0), _cmd(command)
{
}

/**
 * @details Destroys the CommandReport object.
 */
CommandReport::~CommandReport()
{
}

void CommandReport::addStdOut(const QString& msg)
{
    _stdout += msg + "\n";
}

void CommandReport::addStdErr(const QString& msg)
{
    _stderr += msg + "\n";
}

} // namespace hic
