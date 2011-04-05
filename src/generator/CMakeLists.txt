SUBPACKAGE(generator system hardware)
set( generator_src
    src/StateController.cpp
    src/AbstractGenerator.cpp
)
set( moc_headers
     StateController.h
     )
QT4_WRAP_CPP( generator_src ${moc_headers} )
SUBPACKAGE_LIBRARY(generator ${generator_src} )

add_subdirectory(test)
