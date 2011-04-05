SUBPACKAGE(lofarTest lofar hardwareTest )
set(
   lofarTest_src
   src/lofarTest.cpp
   src/LofarTest.cpp
   src/LofarBeamTest.cpp
#   src/LCU_GeneratorTest.cpp
)
add_executable(lofarTest ${lofarTest_src} )
target_link_libraries(lofarTest ${SUBPACKAGE_LIBRARIES} ${CPPUNIT_LIBRARIES} )
add_test(lofarTest lofarTest )
