#ifndef SELECTIONPARAMETERINTERFACE_H
#define SELECTIONPARAMETERINTERFACE_H
#include <QList>
#include <QString>
#include "ParameterQObject.h"


/**
 * @file SelectionParameterInterface.h
 */

namespace hic {


/**
 * @class SelectionParameterInterface
 * 
 * @brief
 *    Main interface for the SelectionParamterInterface
 * @details
 * 
 */
class SelectionParameterInterface : public ParameterQObject
{
    Q_OBJECT

    public:
        /// SelectionParameterInterface constructor.
        SelectionParameterInterface( const QString& name, const QString& doc );

        /// SelectionParameterInterface destructor.
        virtual ~SelectionParameterInterface();

        // return a list of decscriptors for the allowable
        //  values
        const QList<QString>& allowableValues() const;

        /// return the current indes relative to allowed values
        int currentIndex() const { return _currentIndex; }

        QString toString() const { return _allowable[_currentIndex]; };

    public slots:
        void setFromIndex(int index);

    protected:
        /// set the value to that corresponding to
        //  the specfied descriptor
        virtual Report _setFromString(const QString&);

    protected:
        QList<QString> _allowable;
        int _currentIndex;

    private:
};

} // namespace hic

#endif // SELECTIONPARAMETERINTERFACE_H 
