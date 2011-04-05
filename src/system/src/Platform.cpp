/*
 * Copyright (c) 2011, The University of Oxford
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the University of Oxford nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
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
   : QObject(0)
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
