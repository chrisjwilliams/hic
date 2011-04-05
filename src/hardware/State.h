#ifndef STATE_H
#define STATE_H

#include <QObject>
#include <QList>
#include <QString>
#include "ParameterGroup.h"
#include <boost/shared_ptr.hpp>

/**
 * @file State.h
 */

namespace hic {
    class ParameterGroup;

/**
 * @class State
 * 
 * @brief
 *    Manages and groups Parameters that define a state
 * @details
 * 
 */
class State : public QObject
{
    Q_OBJECT

    protected:
        State(const State&); // make copy constructor protected
                             // to avoid any slicing issues

    public:
        /// State constructor.
        State(bool candeactivate = false, QObject* parent = 0);

        /// State destructor.
        virtual ~State();

        /// creates a deep-copy clone of the object
        //  keep this virtual to avoid subtle errors where the
        //  base class does not implement this
//        virtual State* clone() const = 0; // e.g. { return new State( *this ); }

        /// the name of the state
        void setName(const QString& name) { _name = name; };
        const QString& name() const { return _name; };

        /// return a list of all the states in thier logical groups
        virtual const QList<ParameterGroup >& groups() const { return _groups; };

        /// returns a list of substates for advanced configuration etc.
        virtual const QList<State*>& subStates() const { return _states; };

        /// append a group to the state
        void appendGroup(const ParameterGroup& g) { _groups.append(g); };

        /// add a subState
        void addSubState(State*);

        /// returns true if the state is marked as active
        bool isActive() const { return _active; }

        /// set the activation flag
        void setActiveMode(bool mode) { _active = mode; }

        /// returns true if the active mode is optional
        bool canDeactivate() const { return _canDeactivate; };

    protected:
        QList<ParameterGroup> _groups;
        QList<State*> _states;
        bool _active;
        bool _canDeactivate;

    private:

    private:
        QString _name;
};

} // namespace hic

#endif // STATE_H 
