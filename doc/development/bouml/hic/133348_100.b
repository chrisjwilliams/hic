class MainWidget
!!!152036.cpp!!!	MainWidget(inout interface : MainInterface, inout parent : QWidget = 0)

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
!!!152420.cpp!!!	_statusUpdate(in msg : QString) : void
    _statusMsg = msg + " ... ";
    //_status->setText(_statusMsg);
    _status->append(_statusMsg);
!!!152548.cpp!!!	_statusUpdateReport(in r : Report) : void
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
!!!152292.cpp!!!	_setupState() : void
    Report r = _api->setState( *(_stateWidget->definedState()) );

    _statusUpdateReport(r);
    // update report window
    emit report( r );
