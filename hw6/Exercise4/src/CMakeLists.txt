cmake_minimum_required( VERSION 3.12 )
project( loopOut VERSION 1.0 )

add_executable( loopOut loopNewton.cpp )

install( TARGETS loopOut DESTINATION . )

