#include "PlatformTest.h"
#include "system/Platform.h"


namespace hic {

CPPUNIT_TEST_SUITE_REGISTRATION( PlatformTest );
/**
 * @details Constructs a PlatformTest object.
 */
PlatformTest::PlatformTest()
    : CppUnit::TestFixture()
{
}

/**
 * @details Destroys the PlatformTest object.
 */
PlatformTest::~PlatformTest()
{
}

void PlatformTest::setUp()
{
}

void PlatformTest::tearDown()
{
}

void PlatformTest::test_method()
{
    // Use Case:
    // copy doesn't cause problems
    Platform p1("test");
    Platform p2(p1);
    CPPUNIT_ASSERT( p2.name() == "test"  );
}

} // namespace hic
