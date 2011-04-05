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
