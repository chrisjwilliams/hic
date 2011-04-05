#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QString>
#include "system/Report.h"
class QTextEdit;
class QErrorMessage;

/* Class      : MainWidget
 * Revision   : $Rev$ 
 * Description:
 *   Displays interface for selecting state views etc.
 */

namespace hic {
    class MainInterface;
    class StateWidget;
    class Report;

class MainWidget : public QWidget
{
    Q_OBJECT

    public:
        MainWidget( MainInterface* interface, QWidget* parent=0 );
        ~MainWidget();

    protected slots:
        void _setupState();
        void _statusUpdate(const QString&);
        void _statusUpdateReport(const Report& r);

    signals:
        void report(Report);

    private:
        MainInterface* _api;
        StateWidget* _stateWidget;
        QTextEdit* _status;
        QErrorMessage* _errors;
        QString _statusMsg;
};

} // end namespace hic

#endif // MAINWIDGET_H 
