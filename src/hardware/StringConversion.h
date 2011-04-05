#ifndef STRINGCONVERSION_H
#define STRINGCONVERSION_H

#include <QString>

namespace hic {

// some string convertor functions for standard types
/*
inline QString toString(int num) { return QString().setNum(num); };
inline QString toString(unsigned int num) { return QString().setNum(num); };
inline QString toString(float num) { return QString().setNum(num); };
inline QString toString(double num) { return QString().setNum(num); };
*/

template<typename T>
class Convertor{
    public:
        static T fromString(const QString&);
        static QString toString(const T&);
};

} // namespace hic

#endif // STRINGCONVERSION_H
