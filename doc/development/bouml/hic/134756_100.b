class LCU_Generator
!!!160100.cpp!!!	LCU_Generator(inout config : Config)
    _lcu_platform.setHost(config.getParam("LCU", "host", 
                boost::shared_ptr<SingleParameter<QString> >( new SingleParameter<QString>("host","the hostname or ip of the LCU unit" ) )) );
//    _lcu_platform.setPort(config.getParam("LCU", "port", 
//                boost::shared_ptr<SingleParameter<QString> >( new SingleParameter<QString>("port","the ssh connection port on the LCU unit" ) )) );
!!!160356.cpp!!!	setState(in state : State) : Procedure
    if( state.name() == "LofarBeams" )
    {
        return setState( static_cast<const LofarBeams& >(state) );
    }
    Procedure p;
    return p;
!!!160612.cpp!!!	stop() : Procedure
    Procedure p;
    CommandsItem cmds( _lcu_platform );
    cmds.setStatusMessage("Shutting down beams");
    Command c("killall -q beamctl");
    QSet<int> codes;
    c.setExpectedExitCodes(codes << 0 << 1);
    cmds.appendCommand(c);
    p.appendProcedure(cmds);
    return p;
!!!160484.cpp!!!	setState(in state : LofarBeams) : Procedure
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
