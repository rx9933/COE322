cmake_minimum_required(VERSION 3.12)
project(hw12 VERSION 1.0)

find_package( range-v3 REQUIRED )

add_executable(hw12 perfectRanges.cpp)
target_link_libraries( hw12 PUBLIC range-v3::range-v3 )
install(TARGETS hw12 DESTINATION .)
