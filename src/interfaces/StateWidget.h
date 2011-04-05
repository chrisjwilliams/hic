#ifndef STATEWIDGET_H
#define STATEWIDGET_H

#include <QWidget>
#include "hardware/State.h"

class QTabWidget;
class QVBoxLayout;

/**
 * @file StateWidget.h
 */

namespace hic {

/**
 * @class StateWidget
 * 
 * @brief
 * 
 * @details
 * 
 */
class StateWidget : public QWidget
{
    Q_OBJECT

    public:
        /// StateWidget constructor.
        StateWidget(State* state, QWidget* parent=0);

        /// StateWidget destructor.
        ~StateWidget();

        /// get the current state definition
        const State* definedState() const;

    protected:
        void _setup(const State&, QVBoxLayout* layout);

    private:
        QTabWidget* _stateTabs;
        State* _state;
};

} // namespace hic

#endif // STATEWIDGET_H 
