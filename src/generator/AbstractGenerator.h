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
#ifndef ABSTRACTGENERATOR_H
#define ABSTRACTGENERATOR_H

/**
 * @file AbstractGenerator.h
 */

namespace hic {
    class Procedure;
    class State;
    class LocalHost;

/**
 * @class AbstractGenerator
 * 
 * @brief
 *    Base class that represents a state generator plug-in.
 * @details
 *    The function of a generator is to produce the steps required
 *    to realise a specific state. This can be done either directly
 *    or indirectly via a Process object
 * 
 */
class AbstractGenerator
{
    public:
        /// AbstractGenerator constructor.
        AbstractGenerator();

        /// AbstractGenerator destructor.
        virtual ~AbstractGenerator();

        /// stop the state if it is active
        virtual Procedure stop() const;

        /// generates the necessary commands to realise the passed state
        virtual Procedure setState( const State& ) const = 0;

        /// returns a LocalHost platfrom
        LocalHost localhost() const;

    private:
};

} // namespace hic

#endif // ABSTRACTGENERATOR_H 
