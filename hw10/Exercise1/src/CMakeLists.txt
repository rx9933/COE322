## Name: Arushi Sadam
## UT EID: ars7724
## TACC ID: a2097855

cmake_minimum_required( VERSION 3.17 )
project( exercise1TDD VERSION 1.0 )

##
## Extra packages: catch2
##
find_package( PkgConfig REQUIRED )
pkg_check_modules( CATCH2 REQUIRED catch2-with-main )

add_executable( tddtest
    tddTest.cpp tdd.cpp tdd.hpp )

target_include_directories(
                            tddtest PUBLIC ${CATCH2_INCLUDE_DIRS}
                            )

target_link_directories(
        tddtest PUBLIC ${CATCH2_LIBRARY_DIRS}
        )
target_link_libraries(
        tddtest PUBLIC ${CATCH2_LIBRARIES}
        )

set_target_properties(
        tddtest PROPERTIES
        BUILD_RPATH   "${CATCH2_LIBRARY_DIRS}"
        INSTALL_RPATH "${CATCH2_LIBRARY_DIRS}"
    )

target_compile_features( tddtest PRIVATE cxx_std_17 )
