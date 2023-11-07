/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2017-2023 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** findzeroclass.cxx : root finding library based on OOP
 ****
 ****************************************************************/
/*
  used/modified by:
  Name: Arushi Sadam
  UT EID: ars7724
  TACC ID: a2097855
 */

//using vectors to input coefficients of polynomial
#include <vector>

class polynomial {
private:
  std::vector<double> coefficients; // coefficient vector
public:
  polynomial( std::vector<double> c ); // constructor for a polynomial based on coefficients
  bool is_odd() const; // checks if largest degree of polynomial is odd
  double evaluate_at(double x) const; // evaluates polynomial at a given x/input value
  double operator()(double x) const { return evaluate_at(x); }; // operator for easier/cleaner function calls
};

void find_initial_bounds // returns the initial bounds, within which, the x intercept of the given polynomial will be found
( const polynomial&,double &left,double &right);

void move_bounds_closer // squeezes bounds closer, improves the accuracy of the x intercept being determined
( const polynomial&,double& left,double& right,bool trace=false );

double find_zero( const polynomial&,double,bool=false ); // calculates the intercept
