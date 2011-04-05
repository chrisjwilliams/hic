#ifndef LOFARHARDWAREVIEW_H
#define LOFARHARDWAREVIEW_H


#include "State.h"

/**
 * @file LofarHardwareView.h
 */

namespace hic {

/**
 * @class LofarHardwareView
 * 
 * @brief
 *    Description of the lofar Harware and its configuration Parameters
 * @details
 * 
 */
class LofarHardwareView : public State
{
    public:
        /// LofarHardwareView constructor.
        LofarHardwareView();

        /// LofarHardwareView destructor.
        ~LofarHardwareView();

    private:
};

} // namespace hic

#endif // LOFARHARDWAREVIEW_H 
