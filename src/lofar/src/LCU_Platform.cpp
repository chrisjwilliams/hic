#include "LCU_Platform.h"
#include "system/LocalHostExecAgent.h"
#include "system/LocalHostFileTransfer.h"
#include "system/SSH_ExecAgent.h"
#include "system/SSH_FileTransfer.h"


namespace hic {


/**
 * @details Constructs a LCU_Platform object.
 */
LCU_Platform::LCU_Platform()
    : Platform()
{
    //setFileTransferAgent( new LocalHostFileTransfer );
    //setExecAgent( new LocalHostExecAgent );
    setFileTransferAgent( new SSH_FileTransfer );
    setExecAgent( new SSH_ExecAgent );
}

/**
 * @details Destroys the LCU_Platform object.
 */
LCU_Platform::~LCU_Platform()
{
}

void LCU_Platform::setHost( const boost::shared_ptr<SingleParameter<QString> >& host )
{
    _host = host;
    hostUpdated();
    connect( _host.get(), SIGNAL( updated() ), this, SLOT ( hostUpdated() ) );
}

void LCU_Platform::hostUpdated()
{
    std::cout << "hostname = " << _host->toString().toStdString() << std::endl;
    setHostName( _host->toString() );
}

} // namespace hic
