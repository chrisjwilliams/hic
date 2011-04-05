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
#ifndef PROCEDURE_H
#define PROCEDURE_H

#include <QObject>
#include <QString>
#include <QList>
#include "ProcedureItem.h"

/**
 * @file Procedure.h
 */

namespace hic {

/**
 * @class Procedure
 * 
 * @brief
 *   Defines a procedure that can be performed on a specific platform
 * @details
 * 
 */
class Procedure : public QObject
{
    Q_OBJECT

    public:
        /// Procedure constructor.
        Procedure(QObject* parent = 0);

        /// Procedure destructor.
        ~Procedure();

        /// copy contructor
        Procedure( const Procedure& procedure );

        /// insert a procedure to be executed
        void appendProcedure( const ProcedureItem& );

        /// add another procedure to this
        void appendProcedure( const Procedure& );

        /// run ther procedure
        Report exec();

        /// returns true if the Procedure has any content
        bool isValid() const;

    signals:
        void status(const QString& msg);

    private:
        QList<ProcedureItem> _procs;
};

} // namespace hic

#endif // PROCEDURE_H 
