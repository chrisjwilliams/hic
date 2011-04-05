#include "ReportModel.h"


namespace hic {


/**
 * @details Constructs a ReportModel object.
 */
ReportModel::ReportModel(const Report& report, QObject *parent )
    : QAbstractItemModel(parent)
{
    foreach( const CommandReport& command, report.commands() )
    {
        if(command.success())
        {
            setTextColor(Qt::black);
        }
        else
        {
            setTextColor(Qt::red);
        }
    }
}

/**
 * @details Destroys the ReportModel object.
 */
ReportModel::~ReportModel()
{
}

} // namespace hic
