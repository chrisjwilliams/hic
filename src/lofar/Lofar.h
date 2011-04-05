#ifndef LOFAR_H
#define LOFAR_H

#include <QList>
#include <boost/shared_ptr.hpp>
#include "hardware/Range.h"
#include "hardware/SelectionParameter.h"
#include "RCU.h"

/** const
 * @file Lofar.h
 */

namespace hic {
class RCU_Filter;

/**
 * @class Lofar
 * 
 * @brief
 *    Main class to hold objects relating to the Lofar subsystems
 * @details
 * 
 */
class Lofar
{
    public:
        /// Lofar constructor.
        Lofar();

        /// Lofar destructor.
        ~Lofar();

        /* 
         * Methods that allow State manipulation, via parameter objects
         */

        /// return the available clock speeds the array can run at
        //  in MHz
        boost::shared_ptr<SelectionParameter<float> > clockSpeeds() const;

        /* 
         * Methods to provide Information about the Lofar instrument
         */

        /// return available filters for a specific antenna array
        QList<RCU_Filter> filters(const RCU::Array&) const;

        /// return the range of RCU ids available in the specified array
        QList<Range<unsigned int> > rcuIds( const RCU::Array& ) const;

        /// return the base frequency for the given array
        float baseFrequency( const RCU::Array&, const RCU_Filter& ) const;

        /// return the array appropriate for the specified frequency
        RCU::Array array(float frequency, const RCU_Filter&) const;

        /// return the frequency for the given array and subband id
        float frequency( unsigned int subband_id, const RCU::Array&,
                         const RCU_Filter&,
                         float clock = -1.0 ) const;

        /// return the range of frequencies required
        Range<float> frequencyRange( const RCU::Array&, const RCU_Filter&,
                                     float clock ) const;

        /// return the width of each subband
        float subbandWidth( float clock ) const;

        QList<Range<unsigned int> > subbandRanges() const;

        /// return the subband corresponding to the specified frequency
        //  if clock <= 0.0 then it will take the value from the clockSpeeds()
        //  parameter
        unsigned int subband(float frequency, const RCU::Array&, const RCU_Filter&,
                             float clock  = -1.0);

    private:
        boost::shared_ptr<SelectionParameter<float> > _clock; 
};

} // namespace hic

#endif // LOFAR_H 
