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
