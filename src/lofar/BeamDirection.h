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
#ifndef BEAMDIRECTION_H
#define BEAMDIRECTION_H
#include <QString>
#include <QList>
#ifndef m_pi
#define m_pi 3.1415926535
#endif

/**
 * @file BeamDirection.h
 */

namespace hic {

/**
 * @class BeamDirection
 * 
 * @brief
 *    retain inforamtion about the beam pointing direction
 * @details
 * 
 */
class BeamDirection
{
    public:
        /// BeamDirection constructor.
        BeamDirection();
        BeamDirection( float x, float y, const QString& type );

        /// BeamDirection destructor.
        ~BeamDirection();

        float longitudeRadians() const { return _x * m_pi/180.0; };
        float longitudeDegrees() const { return _x; };
        void setLongitude( float deg ) { _x = deg; }
        float latitudeRadians() const { return _y * m_pi/180.0; };
        float latitudeDegrees() const { return _y; };
        void setLatitude( float deg ) { _y = deg; }
        inline QString type() const { return _type; };
        void setType( const QString& s ) { _type = s; }

        /// returns true if the values are set and consistent
        bool isValid() const;

        /// return the support direction specification types
        static QList<QString> types();

    private:
        QString _type;
        float _x; // in degrees
        float _y;
};

} // namespace hic

#endif // BEAMDIRECTION_H 
