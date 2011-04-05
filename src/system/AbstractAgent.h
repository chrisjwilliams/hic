#ifndef ABSTRACTAGENT_H
#define ABSTRACTAGENT_H

#include "system/Platform.h"

/**
 * @file AbstractAgent.h
 */

namespace hic {

/**
 * @class AbstractAgent
 * 
 * @brief
 * 
 * @details
 * 
 */
class AbstractAgent
{
    public:
        /// AbstractAgent constructor.
        AbstractAgent();

        /// AbstractAgent destructor.
        ~AbstractAgent();

        /// return the platform associated with this agent
        //  Don't use this in the constructor as it is not be set 
        inline const Platform* platform() const { return _platform; };

        // set the platform
        void setPlatform(const Platform* p) { _platform = p; };

    private:
        const Platform*  _platform;
};

} // namespace hic

#endif // ABSTRACTAGENT_H 
