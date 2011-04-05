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
