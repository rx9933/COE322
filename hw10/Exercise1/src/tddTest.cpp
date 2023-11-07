// define/include catch2 set up/libraries
#define CATCH_CONFIG_MAIN
#include "catch2/catch_all.hpp"
#include "tdd.hpp" // link to the header file, for function declarations

TEST_CASE( "test that f always returns positive" ) { // tests for input values of 5, -1, -100
  int n=5;
  REQUIRE( f(n)>0 ); //require output to be positive
  int o=-1;
  REQUIRE( f(o)>0 ); //require output to be positive
  int p=-100;
  REQUIRE( f(p)>0 ); //require output to be positive
}

///more test cases
TEST_CASE( "more test that f always returns positive" ) { // tests for input values from -100 to 99 inclusive 
  for (int n=-100; n <100; n++)
    {
      INFO("iteration: " << n); // outputs value of n/input
      REQUIRE(f(n)>0); //require output to be positive
    }
}
