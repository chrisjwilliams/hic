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
#include "MainWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QErrorMessage>
#include <QScrollArea>

#include "interfaces/StateWidget.h"
#include "interfaces/MainInterface.h"
#include "system/Report.h"

namespace hic {

// class MainWidget 
MainWidget::MainWidget(MainInterface* interface, QWidget* parent)
    : QWidget(parent), _api(interface)
{

    QVBoxLayout* layout = new QVBoxLayout();

    QScrollArea* scrollArea = new QScrollArea;
    _stateWidget = new StateWidget( _api->startState() );
    scrollArea->setWidget(_stateWidget);
    layout->addWidget(scrollArea);

    // butons to execute the state
    QHBoxLayout* buttonLayout = new QHBoxLayout;
    QPushButton* startButton = new QPushButton(tr("Execute"));
    connect( startButton, SIGNAL( clicked() ),
             this, SLOT( _setupState() ) );
    buttonLayout->addWidget( startButton );

    layout->addLayout(buttonLayout);

    _errors = new QErrorMessage(this);

    // status conso1e
    QScrollArea* statusScrollArea = new QScrollArea;
    _status = new QTextEdit();
    _status->setReadOnly(true);
    statusScrollArea->setWidget( _status );
    statusScrollArea->setWidgetResizable( true );
    layout->addWidget( statusScrollArea );

    setLayout(layout);

    connect ( _api, SIGNAL(  status(const QString&) ),
              this, SLOT ( _statusUpdate(const QString&) ) );
    connect ( _api, SIGNAL(  statusReport(const Report&) ),
              this, SLOT ( _statusUpdateReport(const QString&) ) );
}

MainWidget::~MainWidget()
{
}

void MainWidget::_statusUpdate(const QString& msg)
{
    _statusMsg = msg + " ... ";
    //_status->setText(_statusMsg);
    _status->append(_statusMsg);
}

void MainWidget::_statusUpdateReport(const Report& r)
{
    //_status->movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
    if( ! r.success() )
    {
        _status->setTextColor(Qt::red);
        _status->insertPlainText( tr("Failed\n"));
        _errors->showMessage( r.errorMessage() );
        r.dump();
    }
    else
    {
        _status->setTextColor(Qt::green);
        _status->insertPlainText( tr("OK\n"));
    }
    _status->setTextColor(Qt::black);
}

void MainWidget::_setupState()
{
    Report r = _api->setState( *(_stateWidget->definedState()) );

    _statusUpdateReport(r);
    // update report window
    emit report( r );
}

} // end namespace hic
