#include <QApplication>
#include <iostream>
#include "MainWidget.h"
#include "MainInterface.h"

using namespace hic;

int main(int argc, char** argv )
{

    QApplication app(argc,argv);
    MainInterface api(argc,argv);
    MainWidget widget(&api);
    widget.show();
    return app.exec();
}
