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
#ifndef PLATFORM_H
#define PLATFORM_H

#include <QObject>
#include <QList>
#include <QString>
#include <boost/shared_ptr.hpp>

/**
 * @file Platform.h
 */

namespace hic {
    class Report;
    class AbstractFileTransfer;
    class AbstractExecAgent;
    class Command;

/**
 * @class Platform
 * 
 * @brief
 *   Base class for Accessing different platforms
 * @details
 *   Inheriting class must call the
 *   setFileTransferAgent() method in its constructor
 * 
 */
class Platform : public QObject
{
    Q_OBJECT

    public:
        /// Platform constructor.
        Platform(const QString& name = "", QObject* parent = 0 );
        Platform(const Platform&);

        /// Platform destructor.
        virtual ~Platform();

        /// return a descriptive name for the platform
        const QString& name() const { return _name; }
        void setHostName(const QString& host) { _name = host; };

        /// execute the commands on the specified platform
        Report exec( const QList<Command>& ) const;

        /// methods to move files to/from the platform
        Report getFile(const QString& remote_filename, 
                       const QString& local_filename ) const;
        Report putFile(const QString& local_filename, 
                       const QString& remote_filename ) const;

    protected:
        void setFileTransferAgent(AbstractFileTransfer*); // must be called be inheriting class
        void setExecAgent(AbstractExecAgent*); // must be called be inheriting class

    private:
        boost::shared_ptr<AbstractFileTransfer>   _fileTransferAgent;
        boost::shared_ptr<AbstractExecAgent>      _execAgent;
        QString                                   _name;
};

} // namespace hic

#endif // PLATFORM_H 
