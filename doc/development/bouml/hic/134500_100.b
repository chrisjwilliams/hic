class ReportViewer
!!!157668.cpp!!!	ReportViewer(inout parent : QWidget = 0)
    QTreeView* view = new QTreeView;
    view->setWindowTitle(QObject::tr("Execution Report"));
    view->show();
