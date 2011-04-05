#ifndef PROCEDUREITEMIMPL_H
#define PROCEDUREITEMIMPL_H
#include "system/Platform.h"


/**
 * @file ProcedureItemImpl.h
 */

namespace hic {
    class Report;
    class ProcedureItem;

/**
 * @class ProcedureItemImpl
 * 
 * @brief
 *   Abstract base class for implementation details of a ProcedureItem object
 * @details
 * 
 */
class ProcedureItemImpl
{
    // This class should only be used through the ProcedureItem class
    // can only be called by inheriting classes and the ProcedureItem
    friend class ProcedureItem;

    protected:
        /// ProcedureItemImpl constructor.
        ProcedureItemImpl( const Platform& );

        /// ProcedureItemImpl destructor.
        virtual ~ProcedureItemImpl();

        /// convenience function for obtaining the platform object
        const Platform& platform() const;

    public:
        /// execute the procedure
        virtual Report exec() const = 0;

        /// returns true if the item has any content
        virtual bool isValid() const = 0;

    protected:
        const ProcedureItem* _api;
        Platform _platform;

    private:
};

} // namespace hic

#endif // PROCEDUREITEMIMPL_H 
