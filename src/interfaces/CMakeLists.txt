SUBPACKAGE(interfaces lofar generator hardware)

set( interfaces_src
    src/MainWidget.cpp
    src/MainInterface.cpp
    src/StateWidget.cpp
    src/ParameterWidget.cpp
    src/ParamWidgetSelection.cpp
    src/ParamWidgetMultiRange.cpp
    src/ParamWidgetSingleValue.cpp
)

set( interfaces_moc_headers
        ParameterWidget.h
        ParamWidgetSelection.h
        ParamWidgetMultiRange.h
        ParamWidgetSingleValue.h
        StateWidget.h
        MainWidget.h
        MainInterface.h
    )

QT4_WRAP_CPP( interfaces_src ${interfaces_moc_headers} )
SUBPACKAGE_LIBRARY( interfaces ${interfaces_src} )
SUBPACKAGE_SET_EXTERNAL_LIBRARIES( ${QT_QTGUI_LIBRARY} )

add_executable( stateGenerator gui_main.cpp )
target_link_libraries( stateGenerator interfaces ${SUBPACKAGE_LIBRARIES} )

add_subdirectory(test)
