#ifndef STATEPARAMETER_H
#define STATEPARAMETER_H

#include <QList>
#include <QMap>
#include <QString>


/**
 * @file StateParameter.h
 */

namespace hic {
    class SharedResource;

/**
 * @class StateParameter
 *
 * @brief
 *   Contains details about a parameter, such as its name and allowed values
 * and resources to which it refers.
 *
 * @details
 *
 */
class StateParameter
{
    public:
        /// StateParameter constructor.
        StateParameter(const QString& name, const QString& doc);

        /// StateParameter destructor.
        ~StateParameter();

        /// return the name of the parameter
        const QString& name() const { return _name; };

        /// return the documentation to explain the parameter to a user
        const QString& doc() const { return _doc; };

        /// returns a list of allowed options in a human readable format
        QList<QString> restrictedValues() const;

        /// set any restricted values
        void setRestrictedValues( const QMap<QString,QString >& values );

        /// sets a resource to which the parameter refers
        void setResource(SharedResource* resource);

    protected:
        QMap<QString,QString > _restrictedValues;

    private:
        QString _name;
        QString _doc;
};

} // namespace hic

#endif // STATEPARAMETER_H 
