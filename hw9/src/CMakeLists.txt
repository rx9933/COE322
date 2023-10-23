cmake_minimum_required( VERSION 3.12 )
project(linkOut VERSION 1.0)
add_executable(linkOut main.c linkfunct.cpp link.hpp )
install(TARGETS linkOut DESTINATION . )