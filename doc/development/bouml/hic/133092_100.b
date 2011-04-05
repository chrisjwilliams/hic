class MainInterface
!!!151140.cpp!!!	MainInterface(in  : int, inout  : char, inout parent : QObject = 0)
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
!!!151268.cpp!!!	~MainInterface()
    foreach( State* state, _stateMap )
    {
        delete state;
    }
!!!151396.cpp!!!	startState() : State
    return _stateMap["init"];
!!!151524.cpp!!!	setState(in state : State) : Report
    return _controller.setState(state);
!!!151908.cpp!!!	_statusRecv(in msg : QString) : void
    emit status(msg);
