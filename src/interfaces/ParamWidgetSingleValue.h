#ifndef PARAMWIDGETSINGLEVALUE_H
#define PARAMWIDGETSINGLEVALUE_H


#include "ParameterWidget.h"
#include <boost/shared_ptr.hpp>

class QLineEdit;
class QLabel;

/**
 * @file ParamWidgetSingleValue.h
 */

namespace hic {
    class SingleParameterInterface;

/**
 * @class ParamWidgetSingleValue
 * 
 * @brief
 *    Display and update a Single Value
 * @details
 * 
 */
class ParamWidgetSingleValue : public ParameterWidget
{
    Q_OBJECT

    public:
        /// ParamWidgetSingleValue constructor.
        ParamWidgetSingleValue(boost::shared_ptr<SingleParameterInterface> param,
                                QWidget* parent=0);

        /// ParamWidgetSingleValue destructor.
        ~ParamWidgetSingleValue();

        inline SingleParameterInterface* param() const; 

    protected slots:
        void setParam();

    protected:
        virtual void refresh();
        virtual void selectionUpdate();
        void _setBadColor();
        void _setOKColor();

    private:
        SingleParameterInterface* _mparam;
        QLineEdit* _text;
        QLabel* _rangeLabel;
};

} // namespace hic

#endif // PARAMWIDGETSINGLEVALUE_H 
