/*
 * Copyright (c) 2011, The University of Oxford
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the University of Oxford nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
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
