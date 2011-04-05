# === Set the project name and specify the required CMAKE version.
project(hic CXX C)
cmake_minimum_required(VERSION 2.4)

# === Project version
set(${PROJECT_NAME}_MAJOR_VERSION 0)
set(${PROJECT_NAME}_MINOR_VERSION 0)
set(${PROJECT_NAME}_PATCH_LEVEL 0)

# === Append the src/cmake directory to the module path.
list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake)
include(cmake/packagemacrosNew.cmake)
include(cmake/tags.cmake)

# === Enable the cmake testing framework.
enable_testing()

# === Options and defaults.
if(NOT HIC_INSTALL_DIR)
    set(HIC_INSTALL_DIR "hic")
endif(NOT HIC_INSTALL_DIR)

if(NOT LIBRARY_INSTALL_DIR)
    set(LIBRARY_INSTALL_DIR "${HIC_INSTALL_DIR}/lib")
endif(NOT LIBRARY_INSTALL_DIR)

if(NOT INCLUDE_INSTALL_DIR)
    set(INCLUDE_INSTALL_DIR "${HIC_INSTALL_DIR}/include")
endif(NOT INCLUDE_INSTALL_DIR)

if(NOT BINARY_INSTALL_DIR)
    set(BINARY_INSTALL_DIR "${HIC_INSTALL_DIR}/bin")
endif(NOT BINARY_INSTALL_DIR)

include(compilerDefaults)

# === Find Dependencies.
find_package(CppUnit REQUIRED)
find_package(Qt4 REQUIRED)

# === Add directories to the include path (i.e. -I<directory> ...)
include_directories(${PROJECT_SOURCE_DIR} ${QT_INCLUDES})

DECLARE_PROJECT_LIBRARY(hic generator system hardware interfaces)

# == Recurse into sub-directories defined in modules.cmake.
include(modules.cmake)

CREATE_PROJECT_LIBRARY(hic)
