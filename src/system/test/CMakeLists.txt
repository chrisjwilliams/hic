SUBPACKAGE(systemTest system)

set(
   systemTest_src
   src/systemTest.cpp
   src/PlatformTest.cpp
   src/ProcedureTest.cpp
   src/RemoteFileTest.cpp
   src/CommandsItemTest.cpp
)

set(
   systemTestLib_src
   src/TestProcedureItem.cpp
   src/TestProcedureItemImpl.cpp
   )

SUBPACKAGE_LIBRARY(systemTestUtils ${systemTestLib_src})
add_executable(systemTest ${systemTest_src} )
target_link_libraries(systemTest ${SUBPACKAGE_LIBRARIES} ${CPPUNIT_LIBRARIES} )
add_test(systemTest systemTest )
