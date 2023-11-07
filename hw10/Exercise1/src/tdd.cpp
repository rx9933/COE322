/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2016-2022 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** tdd.cxx : example of catch2 main
 ****
 ****************************************************************/
/*
  modified/used by:
  Name:Arushi Sadam
  UT EID: ars7724
  TACC ID: a2097855
 */

// using standard input/output and library for math
#include <iostream>
#include <cmath>
#include "tdd.hpp" // header file

double f(int n) { return double(abs(n)+1.1);} // returns the double of the absolute value of n + 1.1
//+1.1 ensures an input of 0 also results in a positive output
