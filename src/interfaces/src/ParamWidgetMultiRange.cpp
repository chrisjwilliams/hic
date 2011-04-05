#include "ParamWidgetMultiRange.h"
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include "hardware/MultiRangeParameterInterface.h"
#include "system/Report.h"
#include <iostream>

namespace hic {


/**
 * @details Constructs a ParamWidgetMultiRange object.
 */
ParamWidgetMultiRange::ParamWidgetMultiRange( const boost::shared_ptr<MultiRangeParameterInterface>& param,
                                                 QWidget* parent )
    : ParameterWidget( param, parent)
{
    _mparam = param.get();
    QHBoxLayout* layout = new QHBoxLayout;
    QVBoxLayout* vlayout = new QVBoxLayout;
    QLabel* label = new QLabel(param->name() + ":" );
    _rangeLabel = new QLabel();
    layout->addWidget(label, Qt::AlignRight);
    _text = new QLineEdit;
    vlayout->addWidget( _text );
    vlayout->addWidget(_rangeLabel, Qt::AlignRight);
    layout->addLayout( vlayout );
    setLayout( layout );

    selectionUpdate();
    refresh();

    connect( _text, SIGNAL( textEdited(const QString&) ),
             this , SLOT( setParam() ) );
}

/**
 * @details Destroys the ParamWidgetSelection object.
 */
ParamWidgetMultiRange::~ParamWidgetMultiRange()
{
}

void ParamWidgetMultiRange::setParam()
{
    Report r = param()->setFromString( _text->text() );
    if( ! r.success() )
    {
        std::cout << "new param::bad : " << r.errorMessage().toStdString() << std::endl;
        _setBadColor();
    }
    else {
    //std::cout << "new param::ok" << std::endl;
        _setOKColor();
    }
}

QString ParamWidgetMultiRange::doc() const
{
    return QString("Multi-Range Specification Format example: 1")
            + param()->spanIndicator()  + "5"
            + param()->rangeSeperator() + "8" 
            + param()->rangeSeperator() + "10"
            + param()->rangeSeperator() + "20"
            + param()->spanIndicator()  + "25";
}

void ParamWidgetMultiRange::refresh()
{
    _rangeLabel->setText( QString("min:") +
                    _mparam->minimum() + "\nmax:" +
                    _mparam->maximum() );
    Report r = param()->validateString( _text->text() );
    if( r.success() ) {
        _setOKColor();
    }
    else {
        _setBadColor();
    }
}

void ParamWidgetMultiRange::selectionUpdate()
{
    _text->setText( param()->toString() );
}

MultiRangeParameterInterface* ParamWidgetMultiRange::param() const
{
    return _mparam;
}

void ParamWidgetMultiRange::_setOKColor()
{
    QPalette pal = _text->palette();
    pal.setColor( QPalette::Text, Qt::black );
    _text->setPalette(pal);
}

void ParamWidgetMultiRange::_setBadColor()
{
    QPalette pal = _text->palette();
    pal.setColor( QPalette::Text, Qt::red );
    _text->setPalette(pal);
}
} // namespace hic
