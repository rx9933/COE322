cmake_minimum_required(VERSION 3.12)
project(NamedVectorInheritance)

set(CMAKE_CXX_STANDARD 14)

# Set the installation directory
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/install)

add_executable(inheritanceOut namedVector.cpp)

# Install the executable to the specified directory
install(TARGETS inheritanceOut DESTINATION ${CMAKE_INSTALL_PREFIX})
