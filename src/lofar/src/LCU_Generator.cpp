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
#include "LCU_Generator.h"
#include <iostream>

#include "lofar/LofarBeam.h"
#include "lofar/LofarBeams.h"
#include "lofar/BeamDirection.h"
#include "hardware/State.h"
#include "system/Procedure.h"
#include "system/CommandsItem.h"
#include "system/Command.h"
#include "hardware/Config.h"

namespace hic {

/**
 * @details Constructs a LCU_Generator object.
 */
LCU_Generator::LCU_Generator( Config& config )
{
    _lcu_platform.setHost(config.getParam("LCU", "host", 
                boost::shared_ptr<SingleParameter<QString> >( new SingleParameter<QString>("host","the hostname or ip of the LCU unit" ) )) );
//    _lcu_platform.setPort(config.getParam("LCU", "port", 
//                boost::shared_ptr<SingleParameter<QString> >( new SingleParameter<QString>("port","the ssh connection port on the LCU unit" ) )) );
}

/**
 * @details Destroys the LCU_Generator object.
 */
LCU_Generator::~LCU_Generator()
{
}

Procedure LCU_Generator::setState(const State& state) const
{
    if( state.name() == "LofarBeams" )
    {
        return setState( static_cast<const LofarBeams& >(state) );
    }
    Procedure p;
    return p;
}

Procedure LCU_Generator::stop() const
{
    Procedure p;
    CommandsItem cmds( _lcu_platform );
    cmds.setStatusMessage("Shutting down beams");
    Command c("killall -q beamctl");
    QSet<int> codes;
    c.setExpectedExitCodes(codes << 0 << 1);
    cmds.appendCommand(c);
    p.appendProcedure(cmds);
    return p;
}

Procedure LCU_Generator::setState(const LofarBeams& state) const
{
    Procedure p;
    CommandsItem cmds( _lcu_platform );
    cmds.setStatusMessage("Starting Beams");
    foreach( const LofarBeam* beam, state.activeBeams() )
    {
        if( beam->isActive() && beam->isValid() )
        {
            QString cmd("nohup beamctl ");
            cmd += QString("--array=") + (beam->array()==RCU::LB?"LBA":"HBA");
            cmd += " --rcus=";
            QString sep="";
            foreach( const RangeT& range , beam->RCU_Ids() ) {
                cmd += sep + range.toString(":");
                sep = ",";
            }
            cmd += " ";
            cmd += "--rcumode=" + QString().setNum(beam->filter().filterId()) + " ";
            //cmd += "--beamlets=" + beam->streams() + " ";
            cmd += "--subbands=";
            sep = "";
            foreach( const RangeT& range , beam->subbands() ) {
                cmd += sep + range.toString(":");
                sep=",";
            }
            cmd += " --direction=" + QString().setNum(beam->direction().longitudeRadians()) + ","
                + QString().setNum(beam->direction().latitudeRadians()) + "," + beam->direction().type() + "";
            cmds.appendCommand(cmd);
        }
    }
    p.appendProcedure(cmds);
    return p;
}

} // namespace hic
