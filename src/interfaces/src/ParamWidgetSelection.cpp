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
#include "ParamWidgetSelection.h"
#include <QHBoxLayout>
#include <QComboBox>
#include <QLabel>


namespace hic {


/**
 * @details Constructs a ParamWidgetSelection object.
 */
ParamWidgetSelection::ParamWidgetSelection( 
                const boost::shared_ptr<SelectionParameterInterface> param, 
                QWidget* parent )
    : ParameterWidget(param, parent), _param(param)
{
    QHBoxLayout* layout = new QHBoxLayout;
    QLabel* label = new QLabel(param->name() + ":" );
    layout->addWidget(label, Qt::AlignRight);
    _combo = new QComboBox;
    layout->addWidget(_combo, Qt::AlignLeft);
    setLayout(layout);

    refresh();

    connect( _combo, SIGNAL(currentIndexChanged(int)) ,
             _param.get(), SLOT(setFromIndex(int)) );
}

/**
 * @details Destroys the ParamWidgetSelection object.
 */
ParamWidgetSelection::~ParamWidgetSelection()
{
}

void ParamWidgetSelection::refresh()
{
    _combo->clear();
    foreach( const QString& option, _param->allowableValues() ) 
    {
        _combo->addItem( option );
    }
}

void ParamWidgetSelection::selectionUpdate()
{
    _combo->setCurrentIndex( _param->currentIndex() );
}

} // namespace hic
