#ifndef TESTPROCEDUREITEM_H
#define TESTPROCEDUREITEM_H


#include "ProcedureItem.h"
#include "system/LocalHost.h"

/**
 * @file TestProcedureItem.h
 */

namespace hic {
    class Platform;

/**
 * @class TestProcedureItem
 * 
 * @brief
 *   A procedure Item for testing
 * @details
 * 
 */
class TestProcedureItem : public ProcedureItem
{
    public:
        /// TestProcedureItem constructor.
        TestProcedureItem(const Platform& p = LocalHost() );

        /// TestProcedureItem destructor.
        ~TestProcedureItem();

    private:
};

} // namespace hic

#endif // TESTPROCEDUREITEM_H 
