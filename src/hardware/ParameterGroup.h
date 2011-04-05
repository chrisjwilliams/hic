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
#ifndef PARAMETERGROUP_H
#define PARAMETERGROUP_H

#include <QString>
#include <QList>
#include <boost/shared_ptr.hpp>
#include "ParameterQObject.h"

/**
 * @file ParameterGroup.h
 */

namespace hic {
class ParameterQObject;

/**
 * @class ParameterGroup
 * 
 * @brief
 *    A named container of StateParameters 
 * @details
 *    The paramters can be activated or deactivated as required
 */
class ParameterGroup
{
    public:
        /// ParameterGroup constructor.
        ParameterGroup(const QString& name);

        /// ParameterGroup destructor.
        ~ParameterGroup();

        /// returns the name of the group
        const QString& name() const;

        /// returns the Parameters in the group
        const QList<boost::shared_ptr<ParameterQObject> >& parameters() const;

        /// returns true if the group can be activated/deactivated
        bool canDeactivate() const;
        void enableDeactivation();

        /// returns true if the group has been activated
        bool isActive() const { return _active; };
        void setActiveState(bool state) { _active = state; };

        /// add a parameter to the group as a shared_ptr
        void addParameter(const boost::shared_ptr<ParameterQObject>& param);

    private:
        QString _name;
        bool _deactivatible;
        bool _active;
        QList< boost::shared_ptr<ParameterQObject> > _params;
};

} // namespace hic

#endif // PARAMETERGROUP_H 
