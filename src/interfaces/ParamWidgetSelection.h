#ifndef PARAMWIDGETSELECTION_H
#define PARAMWIDGETSELECTION_H
#include "ParameterWidget.h"
#include <boost/shared_ptr.hpp>
#include "SelectionParameterInterface.h"


/**
 * @file ParamWidgetSelection.h
 */
class QComboBox;

namespace hic {

/**
 * @class ParamWidgetSelection
 * 
 * @brief
 * 
 * @details
 * 
 */
class ParamWidgetSelection : public ParameterWidget
{
    Q_OBJECT

    public:
        /// ParamWidgetSelection constructor.
        ParamWidgetSelection( const boost::shared_ptr<SelectionParameterInterface> param,
                              QWidget* parent=0);

        /// ParamWidgetSelection destructor.
        ~ParamWidgetSelection();

    protected:
        virtual void refresh();
        virtual void selectionUpdate();

    private:
        const boost::shared_ptr<SelectionParameterInterface> _param;
        QComboBox* _combo;
};

} // namespace hic

#endif // PARAMWIDGETSELECTION_H 
