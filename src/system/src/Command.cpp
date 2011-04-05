#include "Command.h"


namespace hic {


/**
 * @details Constructs a Command object.
 */
Command::Command(const QString& cmd)
    : _cmd(cmd)
{
}

/**
 * @details Destroys the Command object.
 */
Command::~Command()
{
}

void Command::setExpectedExitCodes( const QSet<int>& codes )
{
    _goodCodes += codes;
}

void Command::setExpectedExitCode( int code )
{
    if( !_goodCodes.contains(code) )
        _goodCodes.insert(code);
}

bool Command::isExitCodeExpected(int code) const
{
    // default is to assume 0 for success
    if( _goodCodes.size() == 0 ) {
        return (code==0)?true:false;
    }
    // exit codes are defined so use them instead of
    // the default
    return _goodCodes.contains(code);
}

} // namespace hic
