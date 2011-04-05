#ifndef LOFARBEAMS_H
#define LOFARBEAMS_H

#include "State.h"
#include "LofarBeam.h"
#include "Lofar.h"

/**
 * @file LofarBeams.h
 */

namespace hic {

/**
 * @class LofarBeams
 * 
 * @brief
 *   A top level view of the state of the Lofar Station in terms of Beams
 * @details
 * 
 */
class LofarBeams : public State
{
    public:
        /// LofarBeams constructor.
        LofarBeams();

        /// LofarBeams destructor.
        virtual ~LofarBeams();

        /// cloning operator
        //virtual LofarBeams* clone() const;

        /// add a beam tot he configuration
        void addBeam(LofarBeam* beam);

        /// return a list of defined beams
        const QList<LofarBeam*>& activeBeams() const { return _beams; };

    private:
        QList<LofarBeam*> _beams;
        Lofar _lofar;
};

} // namespace hic

#endif // LOFARBEAMS_H 
