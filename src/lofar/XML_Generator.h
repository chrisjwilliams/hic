#ifndef XML_GENERATOR_H
#define XML_GENERATOR_H


#include "generator/AbstractGenerator.h"

/**
 * @file XML_Generator.h
 */

namespace hic {
    class Platform;
    class LofarBeams;

/**
 * @class XML_Generator
 * 
 * @brief
 *   generate an xml file to describe the configuration of the telescope
 * @details
 * 
 */
class XML_Generator : public AbstractGenerator
{
    public:
        /// XML_Generator constructor.
        XML_Generator( );

        /// XML_Generator destructor.
        ~XML_Generator();

        /// implementation of the Abstract interface for a general state
        virtual Procedure setState(const State& state) const;

        /// generate the commands for a given LofarConfiguration
        Procedure setState(const LofarBeams& state) const;

    private:
};

} // namespace hic

#endif // XML_GENERATOR_H 
