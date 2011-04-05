#ifndef PARAMETERQOBJECT_H
#define PARAMETERQOBJECT_H

#include <QObject>

/**
 * @file ParameterQObject.h
 */

namespace hic {
    class Report;

/**
 * @class ParameterQObject
 * 
 * @brief
 *   A Base class Parameter to allow us to use signals/slots
 * @details
 *  moc does not allow the use of templates, hence we put the signals in
 *  a base class
 * 
 */
class ParameterQObject : public QObject
{
    Q_OBJECT

    public:
        struct Types {
            typedef enum { Range, MultiRange, SingleValue, Selection } typeT;
        };
        typedef ParameterQObject::Types::typeT typeT;

    public:
        /// ParameterQObject constructor.
        ParameterQObject( typeT type, const QString& name, 
                          const QString doc, QObject* parent=0);

        /// ParameterQObject destructor.
        ~ParameterQObject();

        /// return the type of parameter
        inline typeT type() const { return _type; };

        /// return the name of the parameter
        inline const QString& name() const { return _name; }

        /// return the documentation aummary for the parameter
        inline const QString& doc() const { return _doc; }

        /// set documentation
        void setDoc(const QString& doc ) { _doc = doc; }

        /// set the value from a string constant
        Report setFromString(const QString& s);

        /// return a string representation of the parameter value
        virtual QString toString() const = 0;

        /// set the verbosity level
        void setVerbose(int level) { _verbose = level; };

        /// Functions to be implemented
    protected:
        /// Set the variable from a given string
        virtual Report _setFromString(const QString& s) = 0;

        void verbose(const QString&, int level=1) const;

    private:
        // private copy constructor
        ParameterQObject(const ParameterQObject&);

    signals:
        // called when the set of allowed values has
        // changed
        void updated();

        // called when a value has been set
        void updatedSelection();

    private:
        typeT _type;
        QString _name;
        QString _doc;
        int _verbose;
};

} // namespace hic

#endif // PARAMETERQOBJECT_H 
