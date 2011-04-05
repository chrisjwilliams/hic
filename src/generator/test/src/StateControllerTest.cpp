#include "StateControllerTest.h"
#include "TestGenerator.h"
#include "generator/StateController.h"
#include "system/Report.h"
#include "hardware/test/TestState.h"


namespace hic {

CPPUNIT_TEST_SUITE_REGISTRATION( StateControllerTest );
/**
 * @details Constructs a StateControllerTest object.
 */
StateControllerTest::StateControllerTest()
    : CppUnit::TestFixture()
{
}

/**
 * @details Destroys the StateControllerTest object.
 */
StateControllerTest::~StateControllerTest()
{
}

void StateControllerTest::setUp()
{
}

void StateControllerTest::tearDown()
{
}

void StateControllerTest::test_method()
{
    {
        // Use Case:
        // No generators
        // Expect:
        // success report
        StateController sc;
        TestState state;
        Report r = sc.setState(state);
        CPPUNIT_ASSERT( r.success() );
    }
    {
        StateController sc;
        TestState state;
        sc.addGenerator(new TestGenerator);
        Report r = sc.setState(state);
        CPPUNIT_ASSERT( r.success() );
    }
}

} // namespace hic
