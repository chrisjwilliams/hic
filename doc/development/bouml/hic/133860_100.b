class ParamWidgetMultiRange
!!!153828.cpp!!!	ParamWidgetMultiRange(in param : boost::shared_ptr<MultiRangeParameterInterface>, inout parent : QWidget = 0)
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
!!!154852.cpp!!!	setParam() : void
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
!!!154084.cpp!!!	doc() : QString
    return QString("Multi-Range Specification Format example: 1")
            + param()->spanIndicator()  + "5"
            + param()->rangeSeperator() + "8" 
            + param()->rangeSeperator() + "10"
            + param()->rangeSeperator() + "20"
            + param()->spanIndicator()  + "25";
!!!154212.cpp!!!	refresh() : void
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
!!!154340.cpp!!!	selectionUpdate() : void
    _text->setText( param()->toString() );
!!!154468.cpp!!!	param() : MultiRangeParameterInterface
    return _mparam;
!!!154724.cpp!!!	_setOKColor() : void
    QPalette pal = _text->palette();
    pal.setColor( QPalette::Text, Qt::black );
    _text->setPalette(pal);
!!!154596.cpp!!!	_setBadColor() : void
    QPalette pal = _text->palette();
    pal.setColor( QPalette::Text, Qt::red );
    _text->setPalette(pal);
