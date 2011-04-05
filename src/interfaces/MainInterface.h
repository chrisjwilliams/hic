#ifndef MAININTERFACE_H
#define MAININTERFACE_H

#include <QObject>
#include <QMap>
#include <QString>
#include "hardware/State.h"
#include "generator/StateController.h"

/**
 * @file MainInterface.h
 */

namespace hic {
    class Report;

/**
 * @class MainInterface
 * 
 * @brief
 *   The primary application interface for all HIC funtionality
 * @details
 * 
 */
class MainInterface : public QObject
{
    Q_OBJECT

    public:
        /// MainInterface constructor.
        MainInterface(int argc, char** argv, QObject* parent = 0);

        /// MainInterface destructor.
        ~MainInterface();

        /// returns the starting state 
        State* startState() const;

        /// setup a specified State
        Report setState(const State& state);

    signals:
        /// emitted each time a status message is generated
        void status(const QString&);
        void statusReport(const Report&);

    private slots:
        void  _statusRecv(const QString&);

    private:
        QMap<QString, State*>    _stateMap;
        StateController          _controller;

};

} // namespace hic

#endif // MAININTERFACE_H 
