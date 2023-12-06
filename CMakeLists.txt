cmake_minimum_required ( VERSION 3.28 )

project ( Foo VERSION 0.1 )

# configure a header file to pass the version number only
configure_file( foover.h.in foover.h )

add_library( Foo STATIC )
add_library( Foo::Foo ALIAS Foo )

target_sources( Foo 
    PRIVATE 
      foo.cpp
)

# make cache variables for install destinations
include(GNUInstallDirs)

message( STATUS "CMAKE_PREFIX_PATH = ${CMAKE_PREFIX_PATH}" )
message( STATUS "CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}" )
message( STATUS "CMAKE_CURRENT_BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}" )
message( STATUS "CMAKE_INSTALL_INCLUDEDIR = ${CMAKE_INSTALL_INCLUDEDIR}" )
message( STATUS "CMAKE_INSTALL_LIBDIR = ${CMAKE_INSTALL_LIBDIR}" )
message( STATUS "CMAKE_INSTALL_BINDIR = ${CMAKE_INSTALL_BINDIR}" )

message( STATUS "Foo_VERSION_MAJOR = ${Foo_VERSION_MAJOR}" )
message( STATUS "Foo_VERSION_MINOR = ${Foo_VERSION_MINOR}" )

set ( PackageName "Foo" )
set ( dest ${CMAKE_INSTALL_LIBDIR}/cmake/${PackageName} )
set ( dest ${CMAKE_INSTALL_LIBDIR}/cmake/${PackageName} )

# add include directories
target_include_directories( Foo
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

include(CMakePrintHelpers)
cmake_print_properties(
  TARGETS ${PROJECT_NAME}
  PROPERTIES INCLUDE_DIRECTORIES
)

cmake_print_properties(
  TARGETS ${PROJECT_NAME}
  PROPERTIES INTERFACE_LINK_DIRECTORIES
)

# install the target and create export-set
install(TARGETS Foo
        EXPORT FooTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# install header file
install(FILES foo.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/foover.h"
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# generate and install export file
install( EXPORT FooTargets
    FILE FooTargets.cmake
    NAMESPACE Foo::
    DESTINATION ${dest}
)

include(CMakePackageConfigHelpers)

# generate the config file that is includes the exports
configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/${PackageName}Config.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/${PackageName}Config.cmake"
  INSTALL_DESTINATION ${dest}
  PATH_VARS CMAKE_INSTALL_INCLUDEDIR
)

# generate the version file for the config file
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/${PackageName}ConfigVersion.cmake"
  VERSION "${Foo_VERSION_MAJOR}.${Foo_VERSION_MINOR}"
  COMPATIBILITY AnyNewerVersion
)

# install config files
install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/${PackageName}Config.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/${PackageName}ConfigVersion.cmake"
  DESTINATION ${dest}
)
