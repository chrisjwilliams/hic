class ParameterWidget
!!!152804.cpp!!!	ParameterWidget(in p : boost::shared_ptr<ParameterQObject>, inout parent : QWidget = 0)
    connect( p.get(), SIGNAL( updated() ),
             this, SLOT( updateData() ) );
    connect( p.get(), SIGNAL( updatedSelection() ),
             this, SLOT( doSelectionUpdate() ) );
!!!153060.cpp!!!	doc() : QString
    return QString();
!!!153444.cpp!!!	event(inout event : QEvent) : bool
    if (event->type() == QEvent::ToolTip) 
    {
        QHelpEvent *helpEvent = static_cast<QHelpEvent *>(event);
        QToolTip::showText(helpEvent->globalPos(), _param->doc() + "\n" + doc() );
    }
    return QWidget::event(event);
!!!153572.cpp!!!	updateData() : void
    refresh();
!!!153700.cpp!!!	doSelectionUpdate() : void
    selectionUpdate();
