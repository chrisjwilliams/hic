#ifndef SELECTIONPARAMETER_H
#define SELECTIONPARAMETER_H


#include "SelectionParameterInterface.h"
#include <iostream>

/**
 * @file SelectionParameter.h
 */

namespace hic {

/**
 * @class SelectionParameter
 * 
 * @brief
 *   Templated extension to the base SelectionParameterInterface
 * @details
 *   provide a value mapping from the descriptors
 * 
 */
template<typename T>
class SelectionParameter : public SelectionParameterInterface
{
    public:
        /// SelectionParameter constructor.
        SelectionParameter(const QString& name, const QString& doc)
            : SelectionParameterInterface( name, doc) { };

        /// SelectionParameter destructor.
        ~SelectionParameter() {};

        void setAllowableValues( const QList<QString>& descriptors, const QList<T>& vals ) { 
            _allowable = descriptors;
            _allowableVals = vals;
            emit updated();
        };

        void set( const T& val ) {
            int current = _allowableVals.indexOf(val);
            if( current >= 0 && current != _currentIndex )
            {
                _currentIndex = current;
                emit ParameterQObject::updatedSelection();
            }
        }

        const QList<T>& allowedVals() const { return _allowableVals; };

        const T& value() const { 
            verbose(QString("value() current item is number ") + 
                    QString().setNum(_currentIndex) + " of " + 
                    QString().setNum(_allowableVals.size()) );
            return _allowableVals[_currentIndex];
        }

    private:
        QList<T> _allowableVals;
};

} // namespace hic

#endif // SELECTIONPARAMETER_H 
