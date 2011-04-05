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
