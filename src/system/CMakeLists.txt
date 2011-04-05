SUBPACKAGE(system)
set( system_src
    # Agents
    src/AbstractAgent.cpp
    src/AbstractFileTransfer.cpp
    src/SSH_FileTransfer.cpp
    src/LocalHostFileTransfer.cpp
    src/AbstractExecAgent.cpp
    src/LocalHostExecAgent.cpp
    src/SSH_ExecAgent.cpp

    # Platforms
    src/Platform.cpp
    src/LocalHost.cpp

    # Other
    src/Procedure.cpp
    src/ProcedureItem.cpp
    src/ProcedureItemImpl.cpp
    src/Report.cpp
    src/Command.cpp
    src/CommandReport.cpp
    src/CommandsItem.cpp
    src/CommandsItemImpl.cpp
    src/FileItem.cpp
    src/FileItemImpl.cpp
    src/RemoteFile.cpp
)
set ( moc_headers
      Procedure.h
      Platform.h
      )

QT4_WRAP_CPP( system_src ${moc_headers} )
SUBPACKAGE_LIBRARY(system ${system_src} )
SUBPACKAGE_SET_EXTERNAL_LIBRARIES( ${QT_QTCORE_LIBRARY} )

add_subdirectory(test)
