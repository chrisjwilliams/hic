class BeamDirection
!!!159844.cpp!!!	isValid() : bool
    return _type != "undefined";
!!!159972.cpp!!!	types() : QList<QString>
    QList<QString> list;
    list << "J2000" << "AZEL" << "LOFAR_LMN" << "SKYSCAN";
    return list;
