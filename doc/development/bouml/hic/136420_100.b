class XML_Generator
!!!169700.cpp!!!	setState(in state : State) : Procedure
    if( state.name() == "LofarBeams" )
    {
        return setState( static_cast<const LofarBeams&>(state) );
    }
    Procedure p;
    return p;
!!!169828.cpp!!!	setState(in state : LofarBeams) : Procedure
    Procedure p;
    int count = 0;
    foreach( const LofarBeam* beam, state.activeBeams() )
    {
        if( beam->isActive() ) {
            FileItem file( localhost() );
            file.setFilename("beam_" + QString().setNum( ++count ) );
            file.append( "<beam>");
            file.append( "<array type=\"" + QString().setNum(beam->array()) + "\">");
            file.append( "</beam>");
            p.appendProcedure( file );
        }
    }
    return p;
