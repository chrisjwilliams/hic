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
#ifndef LCU_PLATFORM_H
#define LCU_PLATFORM_H


#include <QString>
#include "Platform.h"
#include <boost/shared_ptr.hpp>
#include "SingleParameter.h"

/**
 * @file LCU_Platform.h
 */

namespace hic {

/**
 * @class LCU_Platform
 * 
 * @brief
 *   A description of the LCU platform used for controlling the lofar telescope
 * @details
 * 
 */
class LCU_Platform : public Platform
{
    Q_OBJECT

    public:
        /// LCU_Platform constructor.
        LCU_Platform();

        /// LCU_Platform destructor.
        ~LCU_Platform();

        /// set the host from a parameter
        void setHost( const boost::shared_ptr<SingleParameter<QString> >& host );

    protected slots:
        void hostUpdated();

    private:
        boost::shared_ptr<SingleParameter<QString> > _host;
};

} // namespace hic

#endif // LCU_PLATFORM_H 
