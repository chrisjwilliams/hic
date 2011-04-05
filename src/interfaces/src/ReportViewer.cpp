#include "ReportViewer.h"


namespace hic {


/**
 * @details Constructs a ReportViewer object.
 */
ReportViewer::ReportViewer(QWidget* parent)
    : QWidget(parent), _model(0)
{
    QTreeView* view = new QTreeView;
    view->setWindowTitle(QObject::tr("Execution Report"));
    view->show();
}

/**
 * @details Destroys the ReportViewer object.
 */
ReportViewer::~ReportViewer()
{
}

void ReportViewer::view( const Report& report )
{
    // Create the model
    if( _model ) { delete _model; }
    _model = new ReportModel( report );
    foreach( const CommandReport& command, report.commands() )
    {
        if(command.success())
        {
            setTextColor(Qt::black);
        }
        else
        {
            setTextColor(Qt::red);
        }
    }
    view->setModel(&_model);
    view->show();
}

} // namespace hic,
