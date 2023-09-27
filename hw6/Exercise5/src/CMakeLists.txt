cmake_minimum_required( VERSION 3.12 )
project( objectiveNewton VERSION 1.0 )

add_executable( objectiveOut objectiveNewton.cpp )
target_compile_features( objectiveOut PRIVATE cxx_std_17 )

##
## Extra package: cxxopts
##
find_package( PkgConfig REQUIRED )
pkg_check_modules( OPTS REQUIRED cxxopts )
target_include_directories(
        objectiveOut PUBLIC
        ${OPTS_INCLUDE_DIRS}
        )

install( TARGETS objectiveOut DESTINATION . )