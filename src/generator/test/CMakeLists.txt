SUBPACKAGE(generatorTest generator systemTest hardwareTest )
set(
   generatorTest_src
   src/generatorTest.cpp
   src/StateControllerTest.cpp
)
set(
    generatorTestLib_src
    src/TestGenerator.cpp
    )
SUBPACKAGE_LIBRARY(generatorTestUtils ${generatorTestLib_src})
add_executable(generatorTest ${generatorTest_src} )
target_link_libraries(generatorTest ${SUBPACKAGE_LIBRARIES} ${CPPUNIT_LIBRARIES} )
add_test(generatorTest generatorTest )
