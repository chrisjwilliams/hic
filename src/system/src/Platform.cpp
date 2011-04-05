#include "AbstractFileTransfer.h"
#include "AbstractExecAgent.h"
#include "Platform.h"
#include "Report.h"
#include <iostream>

namespace hic {


/**
 * @details Constructs a Platform object.
 */
Platform::Platform(const QString& name, QObject* parent )
    : QObject(parent), _fileTransferAgent( (AbstractFileTransfer*)0 ),
      _execAgent( (AbstractExecAgent*)0 ), _name(name)
{
}

/**
 * @details Destroys the Platform object.
 */
Platform::~Platform()
{
}

Platform::Platform(const Platform& p)
{
    _execAgent = p._execAgent;
    _fileTransferAgent = p._fileTransferAgent;
    _name = p.name();
}

void Platform::setExecAgent(AbstractExecAgent* agent)
{
    Q_ASSERT( agent != 0 );
    _execAgent.reset(agent);
    _execAgent->setPlatform(this);
}

void Platform::setFileTransferAgent(AbstractFileTransfer* agent)
{
    Q_ASSERT( agent != 0 );
    _fileTransferAgent.reset(agent);
    _fileTransferAgent->setPlatform(this);
}
/**
 * @details base class simply executes the commands one by one on the
 * local system. TODO move to LocalHost
 */
Report Platform::exec( const QList<Command>& commands ) const
{
    Q_ASSERT( _execAgent != 0 );
    return _execAgent->exec(commands);
}

/*
 * @details
 * default implementaion assumes the local platform
 * and simply performs a copy
 */
Report Platform::getFile(const QString& remote_filename, const QString& local_filename ) const
{
    Q_ASSERT( _fileTransferAgent != 0 );
    return _fileTransferAgent->getFile(local_filename, remote_filename);
}

/*
 * @details
 * default implementaion assumes the local platform
 * and simply performs a copy
 */
Report Platform::putFile(const QString& local_filename, const QString& remote_filename ) const
{
    Q_ASSERT( _fileTransferAgent != 0 );
    return _fileTransferAgent->putFile(local_filename, remote_filename);
}

} // namespace hic
