#include "ParamWidgetSelection.h"
#include <QHBoxLayout>
#include <QComboBox>
#include <QLabel>


namespace hic {


/**
 * @details Constructs a ParamWidgetSelection object.
 */
ParamWidgetSelection::ParamWidgetSelection( 
                const boost::shared_ptr<SelectionParameterInterface> param, 
                QWidget* parent )
    : ParameterWidget(param, parent), _param(param)
{
    QHBoxLayout* layout = new QHBoxLayout;
    QLabel* label = new QLabel(param->name() + ":" );
    layout->addWidget(label, Qt::AlignRight);
    _combo = new QComboBox;
    layout->addWidget(_combo, Qt::AlignLeft);
    setLayout(layout);

    refresh();

    connect( _combo, SIGNAL(currentIndexChanged(int)) ,
             _param.get(), SLOT(setFromIndex(int)) );
}

/**
 * @details Destroys the ParamWidgetSelection object.
 */
ParamWidgetSelection::~ParamWidgetSelection()
{
}

void ParamWidgetSelection::refresh()
{
    _combo->clear();
    foreach( const QString& option, _param->allowableValues() ) 
    {
        _combo->addItem( option );
    }
}

void ParamWidgetSelection::selectionUpdate()
{
    _combo->setCurrentIndex( _param->currentIndex() );
}

} // namespace hic
