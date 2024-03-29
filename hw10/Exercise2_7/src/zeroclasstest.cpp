/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2017-2023 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** testzero.cxx : unittests for root finding
 ****
 ****************************************************************/
/*
  used by/modified by:
  Name: Arushi Sadam
  UT EID: ars7724
  TACC ID: a2097855
 */
//using standard indput output streams, formatting libraries, vectors
#include <iostream>
using std::cin;
using std::cout;
#include <iomanip>
using std::setw;

#include <vector>
using std::vector;

#include "zeroclasslib.hpp" // link with header file

#define CATCH_CONFIG_MAIN // using CATCH2 for testing
#include "catch2/catch_all.hpp"

TEST_CASE( "proper test","[2]" ) { // checks if can build polynomial
  vector<double> coefficients{3., 2.5, 2.1};
  REQUIRE_NOTHROW( polynomial(coefficients) );

  coefficients.at(0) = 0.;
  REQUIRE_THROWS( polynomial(coefficients) ); // checks if the first coefficient is 0
}


TEST_CASE( "polynomial degree","[3]" ) { // checks if can correctly assign max degree of polynomial based on coefficient vector input
  polynomial second( {2,0,1} ); // 2x^2 + 1
  REQUIRE( not second.is_odd() );
  polynomial third( {3,2,0,1} ); // 3x^3 + 2x^2 + 1
  REQUIRE( third.is_odd() );
}

TEST_CASE( "polynomial evaluation" ) { //checks if polynomial value at particular input is correct
  polynomial second( {2,0,1.1} );
  // correct interpretation: 2x^2 + 1.1
  REQUIRE( second.evaluate_at(2) == Catch::Approx(9.1) );
  // wrong interpretation: 1.1x^2 + 2
  REQUIRE( second.evaluate_at(2) != Catch::Approx(6.4) );
  polynomial third( {3,2,0,1} ); // 3x^3 + 2x^2 + 1
  REQUIRE( third(0) == Catch::Approx(1) );
}

TEST_CASE( "polynomial evaluation again" ) { //checks if polynomial value at particular input is correct
  polynomial second( {2,0,1.1} );
  // correct interpretation: 2x^2 + 1.1
  REQUIRE( second(2) == Catch::Approx(9.1) );
  polynomial third( {3,2,0,1} ); // 3x^3 + 2x^2 + 1
  REQUIRE( third(0) == Catch::Approx(1) );
}

TEST_CASE( "initial bounds" ) { // finds the initial bounds
  double left{10},right{11};
  right = left+1;
  polynomial second( {2,0,1} ); // 2x^2 + 1
  REQUIRE_THROWS( find_initial_bounds(second,left,right) ); // must find an error, as this is even function
  polynomial third( {3,2,0,1} ); // 3x^3 + 2x^2 + 1
  REQUIRE_NOTHROW( find_initial_bounds(third,left,right) ); // must not find an error, as this is an odd function 
  REQUIRE( left<right ); // specifications for finding initial bounds:
  double
    leftval = third(left),
    rightval = third(right);
  REQUIRE( leftval*rightval<=0 );
}


TEST_CASE( "move bounds closer" ) { // squeezing bounds in
  double left{10},right{11};
  polynomial third( {3,2,0,1} ); // 3x^3 + 2x^2 + 1
  REQUIRE_NOTHROW( find_initial_bounds(third,left,right) ); // can evaluate the inital bounds of an odd function
  double
    leftval = third(left), rightval = third(right);
  REQUIRE( leftval*rightval<=0 ); // check conditions again
  REQUIRE_THROWS( move_bounds_closer(third,right,left) );
  REQUIRE_THROWS( move_bounds_closer(third,left,left) );

  double old_left = left, old_right = right; //k conditions again
  REQUIRE_NOTHROW( move_bounds_closer(third,left,right) );
  leftval = third(left); rightval = third(right);
  REQUIRE( leftval*rightval<=0 );
  REQUIRE( ( ( left==old_left and right<old_right ) or
             ( right==old_right and left>old_left ) ) );
}

TEST_CASE( "test zero finder", "[7]" ) { // final evaluation, find the zeros/x intercept
  vector<vector<double>> coefficients{
    {1., 0., 0., 0.01}, // x^3, 3x^2
      {.01, 0., 0., 0., 0., 100000.} // 1/100 x^5 + 10,000 , 1/20 x^4
  };
  for ( int ipoly=0; ipoly<coefficients.size(); ++ipoly ) {
    polynomial oddpoly(coefficients.at(ipoly)); //construct polynomial
    INFO( "polynomial #" << ipoly ); // output polynomial
    double zero, value, prec=1.e-5; // initialize values
    REQUIRE_NOTHROW( zero = find_zero(oddpoly,prec) ); // find the zero
    INFO( "found zero=" << zero ); // output value
    REQUIRE_NOTHROW( value = oddpoly(zero) );
    REQUIRE( std::abs(value)<prec ); // check if within givin precision
  }
}























































