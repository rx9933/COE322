cmake_minimum_required( VERSION 3.12 )
project(linkOut VERSION 1.0)
add_executable(linkOut main.cpp linkfunct.cpp linkshared.hpp )
install(TARGETS linkOut DESTINATION . )