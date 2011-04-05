#include "RCU.h"
#include <QString>


namespace hic {

const RCU::filterMapT RCU::_filters = RCU::_init_map();

/**
 * @details Constructs a RCU object.
 */
RCU::RCU( const RCU::Array& array)
    : _array(array)
{
}

/**
 * @details Destroys the RCU object.
 */
RCU::~RCU()
{
}

RCU::filterMapT RCU::_init_map()
{
    filterMapT _filters;
    _filters[LB] << RCU_Filter("LBL 10MHz HPF")
        << RCU_Filter("LBL 30MHz HPF")
        << RCU_Filter("LBH 10MHz HPF")
        << RCU_Filter("LBH 30MHz HPF");
    _filters[HB] << RCU_Filter("HB 110-190MHz")
        << RCU_Filter("HB 210-270MHz");
    return _filters;
}

inline const QMap<RCU::Array, QList<RCU_Filter> >& RCU::filters() const
{
    return _filters;
}

void RCU::setFilter( const RCU_Filter& filter )
{
    if( ! filterOptions().contains(filter) )
        throw( QString("RCU_Filter %1 not available on this array") );

    _filter = filter;
}

QList<RCU_Filter> RCU::filterOptions() const
{
    return filters().value(_array);
}


} // namespace hic
