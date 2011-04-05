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
#include "ParamWidgetMultiRange.h"
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include "hardware/MultiRangeParameterInterface.h"
#include "system/Report.h"
#include <iostream>

namespace hic {


/**
 * @details Constructs a ParamWidgetMultiRange object.
 */
ParamWidgetMultiRange::ParamWidgetMultiRange( const boost::shared_ptr<MultiRangeParameterInterface>& param,
                                                 QWidget* parent )
    : ParameterWidget( param, parent)
{
    _mparam = param.get();
    QHBoxLayout* layout = new QHBoxLayout;
    QVBoxLayout* vlayout = new QVBoxLayout;
    QLabel* label = new QLabel(param->name() + ":" );
    _rangeLabel = new QLabel();
    layout->addWidget(label, Qt::AlignRight);
    _text = new QLineEdit;
    vlayout->addWidget( _text );
    vlayout->addWidget(_rangeLabel, Qt::AlignRight);
    layout->addLayout( vlayout );
    setLayout( layout );

    selectionUpdate();
    refresh();

    connect( _text, SIGNAL( textEdited(const QString&) ),
             this , SLOT( setParam() ) );
}

/**
 * @details Destroys the ParamWidgetSelection object.
 */
ParamWidgetMultiRange::~ParamWidgetMultiRange()
{
}

void ParamWidgetMultiRange::setParam()
{
    Report r = param()->setFromString( _text->text() );
    if( ! r.success() )
    {
        std::cout << "new param::bad : " << r.errorMessage().toStdString() << std::endl;
        _setBadColor();
    }
    else {
    //std::cout << "new param::ok" << std::endl;
        _setOKColor();
    }
}

QString ParamWidgetMultiRange::doc() const
{
    return QString("Multi-Range Specification Format example: 1")
            + param()->spanIndicator()  + "5"
            + param()->rangeSeperator() + "8" 
            + param()->rangeSeperator() + "10"
            + param()->rangeSeperator() + "20"
            + param()->spanIndicator()  + "25";
}

void ParamWidgetMultiRange::refresh()
{
    _rangeLabel->setText( QString("min:") +
                    _mparam->minimum() + "\nmax:" +
                    _mparam->maximum() );
    Report r = param()->validateString( _text->text() );
    if( r.success() ) {
        _setOKColor();
    }
    else {
        _setBadColor();
    }
}

void ParamWidgetMultiRange::selectionUpdate()
{
    _text->setText( param()->toString() );
}

MultiRangeParameterInterface* ParamWidgetMultiRange::param() const
{
    return _mparam;
}

void ParamWidgetMultiRange::_setOKColor()
{
    QPalette pal = _text->palette();
    pal.setColor( QPalette::Text, Qt::black );
    _text->setPalette(pal);
}

void ParamWidgetMultiRange::_setBadColor()
{
    QPalette pal = _text->palette();
    pal.setColor( QPalette::Text, Qt::red );
    _text->setPalette(pal);
}
} // namespace hic
