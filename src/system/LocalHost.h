#ifndef LOCALHOST_H
#define LOCALHOST_H


#include "Platform.h"

/**
 * @file LocalHost.h
 */

namespace hic {

/**
 * @class LocalHost
 * 
 * @brief
 *    An implementation of the Platform interface for the local host
 * @details
 * 
 */
class LocalHost : public Platform
{
    public:
        /// LocalHost constructor.
        LocalHost();

        /// LocalHost destructor.
        ~LocalHost();

    private:
};

} // namespace hic

#endif // LOCALHOST_H 
