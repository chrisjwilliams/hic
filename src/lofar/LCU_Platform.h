#ifndef LCU_PLATFORM_H
#define LCU_PLATFORM_H


#include <QString>
#include "Platform.h"
#include <boost/shared_ptr.hpp>
#include "SingleParameter.h"

/**
 * @file LCU_Platform.h
 */

namespace hic {

/**
 * @class LCU_Platform
 * 
 * @brief
 *   A description of the LCU platform used for controlling the lofar telescope
 * @details
 * 
 */
class LCU_Platform : public Platform
{
    Q_OBJECT

    public:
        /// LCU_Platform constructor.
        LCU_Platform();

        /// LCU_Platform destructor.
        ~LCU_Platform();

        /// set the host from a parameter
        void setHost( const boost::shared_ptr<SingleParameter<QString> >& host );

    protected slots:
        void hostUpdated();

    private:
        boost::shared_ptr<SingleParameter<QString> > _host;
};

} // namespace hic

#endif // LCU_PLATFORM_H 
