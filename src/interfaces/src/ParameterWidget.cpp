#include "ParameterWidget.h"
#include <QEvent>
#include <QHelpEvent>
#include <QToolTip>


namespace hic {


/**
 * @details Constructs a ParameterWidget object.
 */
ParameterWidget::ParameterWidget(const boost::shared_ptr<ParameterQObject>& p,
                                 QWidget* parent)
    : QWidget(parent), _param(p)
{
    connect( p.get(), SIGNAL( updated() ),
             this, SLOT( updateData() ) );
    connect( p.get(), SIGNAL( updatedSelection() ),
             this, SLOT( doSelectionUpdate() ) );
}

/**
 * @details Destroys the ParameterWidget object.
 */
ParameterWidget::~ParameterWidget()
{
}

// default implementation
QString ParameterWidget::doc() const
{
    return QString();
}

bool ParameterWidget::event( QEvent *event )
{
    if (event->type() == QEvent::ToolTip) 
    {
        QHelpEvent *helpEvent = static_cast<QHelpEvent *>(event);
        QToolTip::showText(helpEvent->globalPos(), _param->doc() + "\n" + doc() );
    }
    return QWidget::event(event);
}

void ParameterWidget::updateData()
{
    refresh();
}

void ParameterWidget::doSelectionUpdate()
{
    selectionUpdate();
}
} // namespace hic
