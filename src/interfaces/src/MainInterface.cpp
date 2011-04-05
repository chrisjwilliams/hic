#include "MainInterface.h"

#include "system/Report.h"
// lofar specific
#include "lofar/LofarBeams.h"
#include "lofar/LofarHardwareView.h"
#include "lofar/LCU_Generator.h"
#include "Config.h"
#include <QDir>
#include <iostream>


namespace hic {


/**
 * @details Constructs a MainInterface object.
 */
MainInterface::MainInterface(int /*argc*/, char** /*argv*/, QObject* parent)
    : QObject(parent)
{
    connect( &_controller, SIGNAL( status(const QString&) ),
             this, SLOT( _statusRecv(const QString&) ) );


    /* 
     * LOFAR specific settings TODO move these out into some configuration module
     */
    _stateMap["init"] = new LofarBeams;
//    _stateMap["init"] = new LofarHardwareView;
    QFile configFile(QDir::homePath() + "/lofarConfig.xml");
    std::cout << "Config file at : " << configFile.fileName().toStdString() << std::endl;
    Config config;
    config.fromXML(configFile);
    _controller.addGenerator( new LCU_Generator(config) );
}

/**
 * @details Destroys the MainInterface object.
 */
MainInterface::~MainInterface()
{
    foreach( State* state, _stateMap )
    {
        delete state;
    }
}

State* MainInterface::startState() const
{
    return _stateMap["init"];
}

Report MainInterface::setState(const State& state)
{
    return _controller.setState(state);
}

void MainInterface::_statusRecv(const QString& msg)
{
    emit status(msg);
}
} // namespace hic
