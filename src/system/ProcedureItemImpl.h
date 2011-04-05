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
#ifndef PROCEDUREITEMIMPL_H
#define PROCEDUREITEMIMPL_H
#include "system/Platform.h"


/**
 * @file ProcedureItemImpl.h
 */

namespace hic {
    class Report;
    class ProcedureItem;

/**
 * @class ProcedureItemImpl
 * 
 * @brief
 *   Abstract base class for implementation details of a ProcedureItem object
 * @details
 * 
 */
class ProcedureItemImpl
{
    // This class should only be used through the ProcedureItem class
    // can only be called by inheriting classes and the ProcedureItem
    friend class ProcedureItem;

    protected:
        /// ProcedureItemImpl constructor.
        ProcedureItemImpl( const Platform& );

        /// ProcedureItemImpl destructor.
        virtual ~ProcedureItemImpl();

        /// convenience function for obtaining the platform object
        const Platform& platform() const;

    public:
        /// execute the procedure
        virtual Report exec() const = 0;

        /// returns true if the item has any content
        virtual bool isValid() const = 0;

    protected:
        const ProcedureItem* _api;
        Platform _platform;

    private:
};

} // namespace hic

#endif // PROCEDUREITEMIMPL_H 
