#ifndef PARAMETERWIDGET_H
#define PARAMETERWIDGET_H

#include <QWidget>

#include "hardware/ParameterQObject.h"
#include <boost/shared_ptr.hpp>

/**
 * @file ParameterWidget.h
 */

namespace hic {

/**
 * @class ParameterWidget
 * 
 * @brief
 *   Base class for all Parameter Widgets
 * @details
 * 
 */
class ParameterWidget : public QWidget
{
    Q_OBJECT

    public:
        /// ParameterWidget constructor.
        ParameterWidget( const boost::shared_ptr<ParameterQObject>& param, 
                         QWidget* parent=0 );

        /// ParameterWidget destructor.
        virtual ~ParameterWidget();

    protected:
        virtual QString doc() const;
        virtual void refresh() = 0;
        virtual void selectionUpdate() = 0;

    protected slots:
        bool event( QEvent *event );
        void updateData();
        void doSelectionUpdate();

    private:
        boost::shared_ptr<ParameterQObject> _param;
};

} // namespace hic

#endif // PARAMETERWIDGET_H 
