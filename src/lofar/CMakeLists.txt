SUBPACKAGE(lofar generator system hardware)
set( lofar_src 
    src/BeamDirection.cpp
    src/LofarBeams.cpp
    src/LofarBeam.cpp
    src/Lofar.cpp
    src/RCU.cpp
    src/RCU_Filter.cpp
    src/LCU_Platform.cpp
    src/LCU_Generator.cpp
    src/XML_Generator.cpp
)
set( lofar_moc_headers
     LofarBeam.h
     LCU_Platform.h
   )
QT4_WRAP_CPP( lofar_src ${lofar_moc_headers} )
SUBPACKAGE_LIBRARY(lofar ${lofar_src} )

add_subdirectory(test)
