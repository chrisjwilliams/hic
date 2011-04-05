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
#ifndef LCU_GENERATOR_H
#define LCU_GENERATOR_H


#include "generator/AbstractGenerator.h"
#include "LCU_Platform.h"
#include "hardware/Range.h"

/**
 * @file LCU_Generator.h
 */

namespace hic {
    class LofarBeams;
    class Config;

/**
 * @class LCU_Generator
 * 
 * @brief
 *    generates the commands required to setup beams on the
 *    lofar stations local control unit
 * @details
 * 
 */
class LCU_Generator : public AbstractGenerator
{
    public:
        /// LCU_Generator constructor.
        LCU_Generator(Config& config);

        /// LCU_Generator destructor.
        ~LCU_Generator();

        /// implementation of the Abstract interface for a general state
        virtual Procedure setState(const State& state) const;

        /// generate the commands for a given LofarBeams
        Procedure setState(const LofarBeams& state) const;

        /// return the procedure to stop the state
        Procedure stop() const;

    private:
        typedef Range<unsigned int> RangeT;

    private:
        LCU_Platform _lcu_platform;
};

} // namespace hic

#endif // LCU_GENERATOR_H 
