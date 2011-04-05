#ifndef PARAMETERGROUP_H
#define PARAMETERGROUP_H

#include <QString>
#include <QList>
#include <boost/shared_ptr.hpp>
#include "ParameterQObject.h"

/**
 * @file ParameterGroup.h
 */

namespace hic {
class ParameterQObject;

/**
 * @class ParameterGroup
 * 
 * @brief
 *    A named container of StateParameters 
 * @details
 *    The paramters can be activated or deactivated as required
 */
class ParameterGroup
{
    public:
        /// ParameterGroup constructor.
        ParameterGroup(const QString& name);

        /// ParameterGroup destructor.
        ~ParameterGroup();

        /// returns the name of the group
        const QString& name() const;

        /// returns the Parameters in the group
        const QList<boost::shared_ptr<ParameterQObject> >& parameters() const;

        /// returns true if the group can be activated/deactivated
        bool canDeactivate() const;
        void enableDeactivation();

        /// returns true if the group has been activated
        bool isActive() const { return _active; };
        void setActiveState(bool state) { _active = state; };

        /// add a parameter to the group as a shared_ptr
        void addParameter(const boost::shared_ptr<ParameterQObject>& param);

    private:
        QString _name;
        bool _deactivatible;
        bool _active;
        QList< boost::shared_ptr<ParameterQObject> > _params;
};

} // namespace hic

#endif // PARAMETERGROUP_H 
