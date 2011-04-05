#ifndef STATECONTROLLER_H
#define STATECONTROLLER_H

#include <QObject>
#include <QList>

/**
 * @file StateController.h
 */

namespace hic {
    class AbstractGenerator;
    class State;
    class Report;

/**
 * @class StateController
 * 
 * @brief
 *   Reads a state definition to set a state
 * @details
 * 
 */
class StateController : public QObject
{
    Q_OBJECT

    public:
        /// StateController constructor.
        StateController( QObject* parent = 0);

        /// StateController destructor.
        ~StateController();

        /// set the state
        Report setState(const State& state);

        /// add a generator for the state
        void addGenerator(AbstractGenerator* generator);

    signals:
        void status(const QString& msg);
        // emit after the state has been executed
        void statusReport(const Report& report);

    protected slots:
        /// emits a status message if appropriate
        void _status(const QString& msg);

    private:
        QList<AbstractGenerator*> _generators;
};

} // namespace hic

#endif // STATECONTROLLER_H 
