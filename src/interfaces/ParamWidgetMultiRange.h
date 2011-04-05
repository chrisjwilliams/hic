#ifndef PARAMWIDGETMULTIRANGE_H
#define PARAMWIDGETMULTIRANGE_H


#include "ParameterWidget.h"
#include <boost/shared_ptr.hpp>

class QLineEdit;
class QLabel;

/**
 * @file ParamWidgetMultiRange.h
 */

namespace hic {
    class MultiRangeParameterInterface;

/**
 * @class ParamWidgetMultiRange
 * 
 * @brief
 *    Widget to display and operate actions on a 
 *    MultiParameterRange
 * @details
 * 
 */
class ParamWidgetMultiRange : public ParameterWidget
{
    Q_OBJECT

    public:
        /// ParamWidgetMultiRange constructor.
        ParamWidgetMultiRange( const boost::shared_ptr<MultiRangeParameterInterface>& param,
                                         QWidget* parent=0 );

        /// ParamWidgetMultiRange destructor.
        ~ParamWidgetMultiRange();

    protected:
        virtual QString doc() const;
        virtual void refresh();
        virtual void selectionUpdate();

        inline MultiRangeParameterInterface* param() const;
        void _setBadColor();
        void _setOKColor();

    protected slots:
        void setParam();


    private:
        MultiRangeParameterInterface* _mparam;
        QLabel* _rangeLabel;
        QLineEdit* _text;
};

} // namespace hic

#endif // PARAMWIDGETMULTIRANGE_H 
