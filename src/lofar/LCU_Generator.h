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
