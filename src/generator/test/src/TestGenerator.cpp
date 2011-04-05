#include "TestGenerator.h"
#include "system/Procedure.h"
#include "system/test/TestProcedureItem.h"


namespace hic {


/**
 * @details Constructs a TestGenerator object.
 */
TestGenerator::TestGenerator()
    : AbstractGenerator()
{
}

/**
 * @details Destroys the TestGenerator object.
 */
TestGenerator::~TestGenerator()
{
}

/// returns a valid Procedure
Procedure TestGenerator::setState(const hic::State&) const
{
    Procedure p;
    TestProcedureItem item;
    p.appendProcedure(item);
    return p;
}

} // namespace hic
