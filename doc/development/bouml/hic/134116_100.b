class ParamWidgetSingleValue
!!!155492.cpp!!!	ParamWidgetSingleValue(in param : boost::shared_ptr<SingleParameterInterface>, inout parent : QWidget = 0)
    _mparam = param.get();
    QHBoxLayout* layout = new QHBoxLayout;
    QVBoxLayout* vlayout = new QVBoxLayout;
    QLabel* label = new QLabel(param->name() + ":" );
    layout->addWidget(label, Qt::AlignRight);
    _text = new QLineEdit;
    vlayout->addWidget( _text );

    // label to inddicate valid range if appropriate
    _rangeLabel = new QLabel();
    vlayout->addWidget(_rangeLabel, Qt::AlignRight);

    layout->addLayout( vlayout );
    setLayout( layout );

    selectionUpdate();
    refresh();

    connect( _text, SIGNAL( textEdited(const QString&) ),
             this , SLOT( setParam() ) );
!!!155876.cpp!!!	setParam() : void
    Report r = param()->setFromString( _text->text() );
    if( ! r.success() )
    {
        _setBadColor();
    }
    else {
        _setOKColor();
    }
!!!156004.cpp!!!	refresh() : void
    if( param()->hasRange() ) {
        _rangeLabel->setText( QString("min:") +
                param()->minimum() + "\nmax:" +
                param()->maximum() );
    }
    Report r = param()->validateString( _text->text() );
    if( r.success() ) {
        _setOKColor();
    }
    else {
        _setBadColor();
    }
!!!156132.cpp!!!	selectionUpdate() : void
    _setOKColor();
    _text->setText( param()->toString() );
!!!155748.cpp!!!	param() : SingleParameterInterface
 
    return _mparam; 
!!!156388.cpp!!!	_setOKColor() : void
    QPalette pal = _text->palette();
    pal.setColor( QPalette::Text, Qt::black );
    _text->setPalette(pal);
!!!156260.cpp!!!	_setBadColor() : void
    QPalette pal = _text->palette();
    pal.setColor( QPalette::Text, Qt::red );
    _text->setPalette(pal);
