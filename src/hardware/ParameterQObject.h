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
#ifndef PARAMETERQOBJECT_H
#define PARAMETERQOBJECT_H

#include <QObject>

/**
 * @file ParameterQObject.h
 */

namespace hic {
    class Report;

/**
 * @class ParameterQObject
 * 
 * @brief
 *   A Base class Parameter to allow us to use signals/slots
 * @details
 *  moc does not allow the use of templates, hence we put the signals in
 *  a base class
 * 
 */
class ParameterQObject : public QObject
{
    Q_OBJECT

    public:
        struct Types {
            typedef enum { Range, MultiRange, SingleValue, Selection } typeT;
        };
        typedef ParameterQObject::Types::typeT typeT;

    public:
        /// ParameterQObject constructor.
        ParameterQObject( typeT type, const QString& name, 
                          const QString doc, QObject* parent=0);

        /// ParameterQObject destructor.
        ~ParameterQObject();

        /// return the type of parameter
        inline typeT type() const { return _type; };

        /// return the name of the parameter
        inline const QString& name() const { return _name; }

        /// return the documentation aummary for the parameter
        inline const QString& doc() const { return _doc; }

        /// set documentation
        void setDoc(const QString& doc ) { _doc = doc; }

        /// set the value from a string constant
        Report setFromString(const QString& s);

        /// return a string representation of the parameter value
        virtual QString toString() const = 0;

        /// set the verbosity level
        void setVerbose(int level) { _verbose = level; };

        /// Functions to be implemented
    protected:
        /// Set the variable from a given string
        virtual Report _setFromString(const QString& s) = 0;

        void verbose(const QString&, int level=1) const;

    private:
        // private copy constructor
        ParameterQObject(const ParameterQObject&);

    signals:
        // called when the set of allowed values has
        // changed
        void updated();

        // called when a value has been set
        void updatedSelection();

    private:
        typeT _type;
        QString _name;
        QString _doc;
        int _verbose;
};

} // namespace hic

#endif // PARAMETERQOBJECT_H 
