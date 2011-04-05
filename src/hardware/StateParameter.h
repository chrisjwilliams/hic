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
#ifndef STATEPARAMETER_H
#define STATEPARAMETER_H

#include <QList>
#include <QMap>
#include <QString>


/**
 * @file StateParameter.h
 */

namespace hic {
    class SharedResource;

/**
 * @class StateParameter
 *
 * @brief
 *   Contains details about a parameter, such as its name and allowed values
 * and resources to which it refers.
 *
 * @details
 *
 */
class StateParameter
{
    public:
        /// StateParameter constructor.
        StateParameter(const QString& name, const QString& doc);

        /// StateParameter destructor.
        ~StateParameter();

        /// return the name of the parameter
        const QString& name() const { return _name; };

        /// return the documentation to explain the parameter to a user
        const QString& doc() const { return _doc; };

        /// returns a list of allowed options in a human readable format
        QList<QString> restrictedValues() const;

        /// set any restricted values
        void setRestrictedValues( const QMap<QString,QString >& values );

        /// sets a resource to which the parameter refers
        void setResource(SharedResource* resource);

    protected:
        QMap<QString,QString > _restrictedValues;

    private:
        QString _name;
        QString _doc;
};

} // namespace hic

#endif // STATEPARAMETER_H 
