class ReportModel
!!!156516.cpp!!!	ReportModel(in report : Report, inout parent : QObject = 0)
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
