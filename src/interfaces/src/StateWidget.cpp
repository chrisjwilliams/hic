#include "StateWidget.h"
#include <QTabWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include "hardware/State.h"
#include "hardware/ParameterGroup.h"
#include "hardware/SelectionParameter.h"
#include "hardware/SingleParameterInterface.h"
#include "interfaces/ParameterWidget.h"
#include "interfaces/ParamWidgetSelection.h"
#include "interfaces/ParamWidgetMultiRange.h"
#include "interfaces/ParamWidgetSingleValue.h"
#include "hardware/ParameterQObject.h"
#include "hardware/MultiRangeParameterInterface.h"

namespace hic {


/**
 * @details Constructs a StateWidget object.
 */
StateWidget::StateWidget(State* state, QWidget* parent)
    : QWidget(parent), _state(state)
{
    _stateTabs = new QTabWidget;

    // set the layout
    QVBoxLayout* layout = new QVBoxLayout;
    _setup(*state, layout);
    layout->setMargin(5);
//    layout->addWidget(menubar);
    layout->addWidget(_stateTabs);
    setLayout(layout);
}

/**
 * @details Destroys the StateWidget object.
 */
StateWidget::~StateWidget()
{
}

void StateWidget::_setup(const State& state, QVBoxLayout* mainlayout)
{
    // Create the state parameters selection dialogues
    QVBoxLayout* layout = mainlayout;
    QGroupBox* enableBox = 0;
    if( state.canDeactivate() ) {
        enableBox = new QGroupBox( tr("enable") );
        enableBox->setCheckable( true );
        enableBox->setChecked( state.isActive() );
        layout = new QVBoxLayout;
    }

    foreach ( const ParameterGroup& group , state.groups() )
    {
        QGroupBox* groupBox = new QGroupBox( group.name() );
        groupBox->setCheckable( group.canDeactivate() );
        groupBox->setChecked( group.isActive() );
        QHBoxLayout* boxlayout = new QHBoxLayout;
        foreach ( const boost::shared_ptr<ParameterQObject>& param , group.parameters() )
        {
            // setup suitable widgets for each parameteR
            ParameterWidget* widget = 0;
            switch ( param->type() )
            {
                case ParameterQObject::Types::Selection:
                    {
                        widget = new ParamWidgetSelection(
                                       boost::static_pointer_cast<
                                                SelectionParameterInterface,
                                                ParameterQObject >(param)
                                 );
                    }
                    break;
                case ParameterQObject::Types::Range:
                    {
                        /*
                        widget = new ParamWidgetRange(
                                   boost::static_pointer_cast<
                                       RangeParameterInterface,
                                       ParameterQObject >(param)
                                 );
                        */
                    }
                    break;
                case ParameterQObject::Types::MultiRange:
                    {
                        widget = new ParamWidgetMultiRange(
                                   boost::static_pointer_cast<
                                       MultiRangeParameterInterface,
                                       ParameterQObject >(param)
                                 );
                    }
                    break;
                case ParameterQObject::Types::SingleValue:
                    {
                        widget = new ParamWidgetSingleValue(
                                   boost::static_pointer_cast<
                                       SingleParameterInterface,
                                       ParameterQObject >(param)
                                 );
                    }
                    break;
                default:
                    break;
            }
            if( widget )
                boxlayout->addWidget( widget, Qt::AlignRight );
        }
        groupBox->setLayout(boxlayout);
        layout->addWidget(groupBox);
    }

    // create a new tab for each sub-state (advanced parameters)
    foreach ( State* substate , state.subStates() ) {
        StateWidget* tab = new StateWidget( substate );
        _stateTabs->addTab( tab , substate->name() );
    }

    if( enableBox ) {
        enableBox->setLayout(layout);
        mainlayout->addWidget(enableBox);
    }
    setLayout(mainlayout);
}

const State* StateWidget::definedState() const
{
    return _state;
}

} // namespace hic
