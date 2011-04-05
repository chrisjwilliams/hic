class ParamWidgetSelection
!!!154980.cpp!!!	ParamWidgetSelection(in param : boost::shared_ptr<SelectionParameterInterface>, inout parent : QWidget = 0)
    QHBoxLayout* layout = new QHBoxLayout;
    QLabel* label = new QLabel(param->name() + ":" );
    layout->addWidget(label, Qt::AlignRight);
    _combo = new QComboBox;
    layout->addWidget(_combo, Qt::AlignLeft);
    setLayout(layout);

    refresh();

    connect( _combo, SIGNAL(currentIndexChanged(int)) ,
             _param.get(), SLOT(setFromIndex(int)) );
!!!155236.cpp!!!	refresh() : void
    _combo->clear();
    foreach( const QString& option, _param->allowableValues() ) 
    {
        _combo->addItem( option );
    }
!!!155364.cpp!!!	selectionUpdate() : void
    _combo->setCurrentIndex( _param->currentIndex() );
