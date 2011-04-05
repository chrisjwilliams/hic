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
