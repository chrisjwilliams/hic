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
#ifndef RCU_FILTER_H
#define RCU_FILTER_H
#include <QString>
#include <QList>


/**
 * @file RCU_Filter.h
 */

namespace hic {
    class Array;

/**
 * @class RCU_Filter
 * 
 * @brief
 *   Container for Filter types that can be applied to RCU units
 * @details
 * 
 */
class RCU_Filter
{
    public:
        enum Type { UNSET, LBL_10MHz_HPF, LBL_30MHz_HPF, LBH_10MHz_HPF,
                    LBH_30MHz_HPF, HB_110MHz, HB_170MHz, HB_210MHz };

    public:
        /// RCU_Filter constructor.
        RCU_Filter();
        RCU_Filter(const QString& type);

        /// RCU_Filter destructor.
        ~RCU_Filter();

        /// return the filter type
        int filterId() const;

        /// return the filters name
        const QString& name() const;

        /// comparision operator
        bool operator==(const RCU_Filter&) const;
        bool operator!=(const RCU_Filter&) const;

        /// select one of the valid filters
        void setType(const QString& type);

        // return a list of options for the filter
        const QList<QString>& options() const;

    private:
        int  _type;
};


} // namespace hic

#endif // RCU_FILTER_H 
