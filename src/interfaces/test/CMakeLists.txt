SUBPACKAGE(interfacesTest interfaces)
set(
   interfacesTest_src
src/interfacesTest.cpp
)
add_executable(interfacesTest ${interfacesTest_src} )
target_link_libraries(interfacesTest ${SUBPACKAGE_LIBRARIES} ${CPPUNIT_LIBRARIES} )
add_test(interfacesTest interfacesTest )
