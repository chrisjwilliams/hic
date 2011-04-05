class RCU
!!!168164.cpp!!!	_init_map() : filterMapT
    filterMapT _filters;
    _filters[LB] << RCU_Filter("LBL 10MHz HPF")
        << RCU_Filter("LBL 30MHz HPF")
        << RCU_Filter("LBH 10MHz HPF")
        << RCU_Filter("LBH 30MHz HPF");
    _filters[HB] << RCU_Filter("HB 110-190MHz")
        << RCU_Filter("HB 210-270MHz");
    return _filters;
!!!168036.cpp!!!	filters() : QMap<Array, QList<RCU_Filter> >
    return _filters;
!!!167908.cpp!!!	setFilter(in filter : RCU_Filter) : void
    if( ! filterOptions().contains(filter) )
        throw( QString("RCU_Filter %1 not available on this array") );

    _filter = filter;
!!!167652.cpp!!!	filterOptions() : QList<RCU_Filter>
    return filters().value(_array);
