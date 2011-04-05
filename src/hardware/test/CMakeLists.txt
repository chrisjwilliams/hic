SUBPACKAGE(hardwareTest hardware)

set(
   hardwareTest_src
   src/hardwareTest.cpp
   src/RangeTest.cpp
   src/MultiRangeParameterTest.cpp
)

set(
    hardwareTestLib_src
    src/TestState.cpp
    )

SUBPACKAGE_LIBRARY(harwareTestUtils ${hardwareTestLib_src} )
add_executable(hardwareTest ${hardwareTest_src} )
target_link_libraries(hardwareTest ${SUBPACKAGE_LIBRARIES} ${CPPUNIT_LIBRARIES} )
add_test(hardwareTest hardwareTest )
