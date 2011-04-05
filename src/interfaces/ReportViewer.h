#ifndef REPORTVIEWER_H
#define REPORTVIEWER_H

#include <QWidget>

/**
 * @file ReportViewer.h
 */

namespace hic {

/**
 * @class ReportViewer
 * 
 * @brief
 *    A Report Viewer
 * @details
 * 
 */
class ReportViewer : public QWidget
{
    Q_OBJECT

    public:
        /// ReportViewer constructor.
        ReportViewer(QWidget* parent=0);

        /// ReportViewer destructor.
        ~ReportViewer();

    private:
        ReportModel* _model;
};

} // namespace hic

#endif // REPORTVIEWER_H 
