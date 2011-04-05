#include "ParamWidgetSingleValue.h"
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include "SingleParameterInterface.h"
#include "system/Report.h"
#include <iostream>


namespace hic {


/**
 * @details Constructs a ParamWidgetSingleValue object.
 */
ParamWidgetSingleValue::ParamWidgetSingleValue(
                        boost::shared_ptr<SingleParameterInterface> param,
                        QWidget* parent)
    : ParameterWidget(param, parent), _text(0), _rangeLabel(0)
{
    _mparam = param.get();
    QHBoxLayout* layout = new QHBoxLayout;
    QVBoxLayout* vlayout = new QVBoxLayout;
    QLabel* label = new QLabel(param->name() + ":" );
    layout->addWidget(label, Qt::AlignRight);
    _text = new QLineEdit;
    vlayout->addWidget( _text );

    // label to inddicate valid range if appropriate
    _rangeLabel = new QLabel();
    vlayout->addWidget(_rangeLabel, Qt::AlignRight);

    layout->addLayout( vlayout );
    setLayout( layout );

    selectionUpdate();
    refresh();

    connect( _text, SIGNAL( textEdited(const QString&) ),
             this , SLOT( setParam() ) );
}

/**
 * @details Destroys the ParamWidgetSingleValue object.
 */
ParamWidgetSingleValue::~ParamWidgetSingleValue()
{
}

void ParamWidgetSingleValue::setParam()
{
    Report r = param()->setFromString( _text->text() );
    if( ! r.success() )
    {
        _setBadColor();
    }
    else {
        _setOKColor();
    }
}

void ParamWidgetSingleValue::refresh()
{
    if( param()->hasRange() ) {
        _rangeLabel->setText( QString("min:") +
                param()->minimum() + "\nmax:" +
                param()->maximum() );
    }
    Report r = param()->validateString( _text->text() );
    if( r.success() ) {
        _setOKColor();
    }
    else {
        _setBadColor();
    }
}

void ParamWidgetSingleValue::selectionUpdate()
{
    _setOKColor();
    _text->setText( param()->toString() );
}

SingleParameterInterface* ParamWidgetSingleValue::param() const { 
    return _mparam; 
}

void ParamWidgetSingleValue::_setOKColor()
{
    QPalette pal = _text->palette();
    pal.setColor( QPalette::Text, Qt::black );
    _text->setPalette(pal);
}

void ParamWidgetSingleValue::_setBadColor()
{
    QPalette pal = _text->palette();
    pal.setColor( QPalette::Text, Qt::red );
    _text->setPalette(pal);
}

} // namespace hic
