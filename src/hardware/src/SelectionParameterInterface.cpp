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
#include "SelectionParameterInterface.h"
#include "system/Report.h"
#include <iostream>


namespace hic {


/**
 * @details Constructs a SelectionParameterInterface object.
 */
SelectionParameterInterface::SelectionParameterInterface( const QString& name, const QString& doc )
    : ParameterQObject( ParameterQObject::Types::Selection, name, doc ), _currentIndex(0)
{
}

/**
 * @details Destroys the SelectionParameterInterface object.
 */
SelectionParameterInterface::~SelectionParameterInterface()
{
}

const QList<QString>& SelectionParameterInterface::allowableValues() const
{
    return _allowable;
}

Report SelectionParameterInterface::_setFromString(const QString& s)
{
    Report r;
    if( ! _allowable.contains(s) ) {
        r.addErrorMessage(s + " is not a valid value for parameter : " 
                            + name() );
    }
    else {
        setFromIndex(_allowable.indexOf(s));
    }
    return r;
} 

void SelectionParameterInterface::setFromIndex(int index)
{
    if( ( index > -1 ) && ( index < _allowable.size( )) )
    {
//    std::cout << this << " SelectionParameterInterface::setFromIndex : index = " << index <<std::endl;
        _currentIndex = index;
        emit updatedSelection();
    }
}

} // namespace hic
