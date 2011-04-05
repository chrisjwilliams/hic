#include "XML_Generator.h"

#include "lofar/LofarBeam.h"
#include "lofar/LofarBeams.h"
#include "lofar/BeamDirection.h"
#include "hardware/State.h"
#include "system/Procedure.h"
#include "system/FileItem.h"
#include "system/LocalHost.h"

namespace hic {


/**
 * @details Constructs a XML_Generator object.
 */
XML_Generator::XML_Generator( )
{
}

/**
 * @details Destroys the XML_Generator object.
 */
XML_Generator::~XML_Generator()
{
}

Procedure XML_Generator::setState(const State& state) const
{
    if( state.name() == "LofarBeams" )
    {
        return setState( static_cast<const LofarBeams&>(state) );
    }
    Procedure p;
    return p;
}

Procedure XML_Generator::setState(const LofarBeams& state) const
{
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
}

} // namespace hic
