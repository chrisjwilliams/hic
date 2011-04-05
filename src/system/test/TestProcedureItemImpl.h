#ifndef TESTPROCEDUREITEMIMPL_H
#define TESTPROCEDUREITEMIMPL_H


#include "ProcedureItemImpl.h"

/**
 * @file TestProcedureItemImpl.h
 */

namespace hic {
    class Report;

/**
 * @class TestProcedureItemImpl
 * 
 * @brief
 * 
 * @details
 * 
 */
class TestProcedureItemImpl : public ProcedureItemImpl
{
    public:
        /// TestProcedureItemImpl constructor.
        TestProcedureItemImpl(const Platform& p);

        /// TestProcedureItemImpl destructor.
        ~TestProcedureItemImpl();

        /// base class required implementations
        bool isValid() const;
        Report exec() const;

    private:
        bool _isValid;
};

} // namespace hic

#endif // TESTPROCEDUREITEMIMPL_H 
