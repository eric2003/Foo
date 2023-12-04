cmake_minimum_required ( VERSION 3.28 )

project ( Foo )

add_library( Foo STATIC )

target_sources( Foo 
    PRIVATE 
      foo.cpp
)


# make cache variables for install destinations
include(GNUInstallDirs)

message( STATUS "CMAKE_PREFIX_PATH = ${CMAKE_PREFIX_PATH}" )
message( STATUS "CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}" )
message( STATUS "CMAKE_INSTALL_INCLUDEDIR = ${CMAKE_INSTALL_INCLUDEDIR}" )
message( STATUS "CMAKE_INSTALL_LIBDIR = ${CMAKE_INSTALL_LIBDIR}" )
message( STATUS "CMAKE_INSTALL_BINDIR = ${CMAKE_INSTALL_BINDIR}" )


set ( PackageName "Foo" )
set ( dest ${CMAKE_INSTALL_LIBDIR}/cmake/${PackageName} )

# add include directories
target_include_directories( Foo
    INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
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
  VERSION "0.0.3"
  COMPATIBILITY AnyNewerVersion
)

# install config files
install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/${PackageName}Config.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/${PackageName}ConfigVersion.cmake"
  DESTINATION ${dest}
)
