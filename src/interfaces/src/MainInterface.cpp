/*
 * Copyright (c) 2011, The University of Oxford
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the University of Oxford nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
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
