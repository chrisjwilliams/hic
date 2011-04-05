#ifndef RCU_H
#define RCU_H

#include <QMap>
#include <QList>
#include "RCU_Filter.h"

/**
 * @file RCU.h
 */

namespace hic {

/**
 * @class RCU
 * 
 * @brief
 *   defines the RCU state and provides generic RCU information
 * @details
 * 
 */
class RCU
{
    public:
        typedef enum { undefined, LB, HB } Array;

    public:
        /// RCU constructor.
        RCU(const Array&);

        /// RCU destructor.
        ~RCU();

        /// returns the id within the array
        /// returns the id within the array
        int id() const { return _id; }

        /// return the various filter options available for this rcu
        QList<RCU_Filter> filterOptions() const;

        /// return the filter channel of the RCU
        RCU_Filter filter() const { return _filter; };

        /// set the filter for the RCU
        //  The RCU_Filter type must be compatible with the Array
        //  otherwise will throw()
        void setFilter( const RCU_Filter& );

    private:
        const QMap<Array, QList<RCU_Filter> >& filters() const;

    private:
        int _id;
        Array _array;
        RCU_Filter _filter; // filter for this RCU
        
        typedef QMap<Array, QList<RCU_Filter> > filterMapT;
        static const filterMapT _filters; // available filters for each array
        static filterMapT _init_map();
    
};

} // namespace hic

#endif // RCU_H 
