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
#include "ParameterQObject.h"
#include "system/Report.h"
#include <iostream>


namespace hic {


/**
 * @details Constructs a ParameterQObject object.
 */
ParameterQObject::ParameterQObject( typeT type, const QString& name, 
                                    const QString doc, QObject* parent)
    : QObject(parent),
      _type(type), _name(name), _doc(doc), _verbose(0)
{
}

/**
 * @details Destroys the ParameterQObject object.
 */
ParameterQObject::~ParameterQObject()
{
}

/// set the value from a string constant
Report ParameterQObject::setFromString(const QString& s)
{
    Report r;
    try {
        // call the specialisation
        r += _setFromString(s);
        if( r.success() )
            emit updatedSelection();
    }
    catch( const Report& err ) {
        r += err;
    }
    catch( const QString& err ) {
        r.addErrorMessage(err);
    }
    return r;
}

void ParameterQObject::verbose(const QString& msg, int level) const
{
    if( _verbose >= level ) {
        std::cout << "Parameter::" << name().toStdString() 
                  << ": " << this << ":" 
                  << msg.toStdString() << std::endl;
    }
}

} // namespace hic
