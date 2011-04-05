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
#ifndef PROCEDUREITEM_H
#define PROCEDUREITEM_H

#include <boost/shared_ptr.hpp>
#include <QString>

/**
 * 
 * @file ProcedureItem.h
 */

namespace hic {
    class Report;
    class ProcedureItemImpl;
    class Platform;

/**
 * @class ProcedureItem
 * 
 * @brief
 *   Base class for items to be inserted into a procedure
 * @details
 *   Wraps an implementation pointer for ease of copying into 
 *   containers etc.
 *
 *   This requires any subclasses to instantiate two
 *   new classes:
 *
 *   One that inherits form ProcedureItemImpl to do the work,
 *   and another one that inherits from this class and instantiats
 *   the  implemenation object in _impl
 * 
 */
class ProcedureItem
{
    public:
        /// ProcedureItem constructor.
        ProcedureItem( const Platform& platform );

        /// ProcedureItem destructor.
        virtual ~ProcedureItem();

        /// execute the procedure
        Report exec() const;

        /// returns true if the item has any content
        bool isValid() const;

        /// return the platform
        //
        /*
        const Platform& platform() const { 
            std::cout << "ProcedureItem:platform: " << _platform.name().toStdString() << std::endl;
            return _platform; }
            */

        /// returns a message suitable for status reporting
        //  that describes the procedure
        const QString& statusMessage() const { return _statusMessage; };

        /// set the message to be returned by statusMessage() 
        void setStatusMessage(const QString& msg) { _statusMessage = msg; }

    private:
        QString _statusMessage;

    protected:
        boost::shared_ptr<ProcedureItemImpl> _impl; // pointer to object that does the work


};

} // namespace hic

#endif // PROCEDUREITEM_H 
