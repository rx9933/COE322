cmake_minimum_required( VERSION 3.17 )
project( exercise1TDD VERSION 1.0 )
##
## Extra packages: catch2
##
find_package( PkgConfig REQUIRED )
pkg_check_modules( CATCH2 REQUIRED catch2-with-main )
##
## main
##

## add_executable( zeromain
##     zeroclassmain.cpp zeroclasslib.cpp zeroclasslib.hpp )
## target_compile_features( zeromain PRIVATE cxx_std_17 )
## target_include_directories(
##                             zeromain PUBLIC ${CATCH2_INCLUDE_DIRS}
##                             )

## set_target_properties(
##      zeromain PROPERTIES
##      BUILD_RPATH   "${CATCH2_LIBRARY_DIRS}"
##      INSTALL_RPATH "${CATCH2_LIBRARY_DIRS}"
##     )
## target_link_directories(
##      zeromain PUBLIC ${CATCH2_LIBRARY_DIRS}
##      )

## target_link_libraries(
##      zeromain PUBLIC ${CATCH2_LIBRARIES}
##      )

##
## tester
##

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
