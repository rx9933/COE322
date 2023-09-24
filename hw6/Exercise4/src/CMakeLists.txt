cmake_minimum_required( VERSION 3.12 )
project( loopOut VERSION 1.0 )

add_executable( loopOut loopNewton.cpp )
target_compile_features( loopOut PRIVATE cxx_std_17 )

##
## Extra package: cxxopts
##
find_package( PkgConfig REQUIRED )
pkg_check_modules( OPTS REQUIRED cxxopts )
target_include_directories(
        loopOut PUBLIC
        ${OPTS_INCLUDE_DIRS}
        )

install( TARGETS loopOut DESTINATION . )

