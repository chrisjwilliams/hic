SUBPACKAGE(hardware system)

set( hardware_src
    src/Config.cpp
    src/State.cpp
    src/SingleParameter.cpp
    src/ParameterGroup.cpp
    src/Parameter.cpp
    src/ParameterQObject.cpp
    src/SelectionParameterInterface.cpp
    src/SingleParameterInterface.cpp
    src/MultiRangeParameterInterface.cpp
    src/StringConversion.cpp
)

set( hardware_moc_headers
    State.h
    ParameterQObject.h
    SelectionParameterInterface.h
   )

QT4_WRAP_CPP( hardware_src ${hardware_moc_headers} )

SUBPACKAGE_LIBRARY( hardware ${hardware_src} )
SUBPACKAGE_SET_EXTERNAL_LIBRARIES( ${QT_QTXML_LIBRARY} ${QT_QTCORE_LIBRARY} )

add_subdirectory(test)
