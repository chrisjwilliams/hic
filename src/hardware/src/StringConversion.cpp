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
#include "StringConversion.h"
#include <QString>


namespace hic {

template<>
int Convertor<int>::fromString(const QString& s) { 
    bool ok; 
    int r=s.toInt(&ok); 
    if( ! ok )
        throw QString("Cannot convert " + s + " to an integer");
    return r;
};

template<>
unsigned int Convertor<unsigned int>::fromString(const QString& s) { 
    bool ok; 
    int r=s.toUInt(&ok); 
    if( ! ok )
        throw QString("Cannot convert " + s + " to an integer");
    return r;
};

template<>
float Convertor<float>::fromString(const QString& s) {
    bool ok; 
    int r=s.toFloat(&ok); 
    if( ! ok )
        throw QString("Cannot convert " + s + " to a float");
    return r;
}

template<>
double Convertor<double>::fromString(const QString& s) {
    bool ok; 
    int r=s.toDouble(&ok); 
    if( ! ok )
        throw QString("Cannot convert " + s + " to a double");
    return r;
}

template<>
QString Convertor<QString>::fromString(const QString& s) { 
    return s; 
}

template<>
QString Convertor<int>::toString(const int& num) { 
    return QString().setNum(num); 
}

template<>
QString Convertor<unsigned int>::toString(const unsigned int& num) { 
    return QString().setNum(num); 
}

template<>
QString Convertor<float>::toString(const float& num) { 
    return QString().setNum(num); 
}

template<>
QString Convertor<double>::toString(const double& num) { 
    return QString().setNum(num); 
}

template<>
QString Convertor<QString>::toString(const QString& s) { 
    return s; };

} // namespace hic
