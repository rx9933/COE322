/*
Name: Arushi Sadam
UT EID: ars7724
TACC Username: rx9933
*/

// include the header file, standard input/output streams, vectors, and the absolute value funciton from the math library.
#include "zeroclasslib.hpp"

#include<iostream>
using std::cout;

#include<vector>
using std::vector;

#include<cmath>
using std::abs;

// constructor, checks if the first coefficient (of the largest independent variable power) is 0
polynomial::polynomial(vector<double> c) // c is inputted coefficients vector
{
  if (c.at(0) == 0)
    {
      throw("zero coefficient"); // largest independent variable power coefficient is 0, so throw erro
    }
  coefficients = c; // assign coefficients vector to the inputted c vector
};

// checks the max degree of the function (which is built upon the coefficients vector)
bool polynomial::is_odd() const
{
  return (coefficients.size()%2== 0); // if even number of coefficients/elements, largest power/degree is odd
}

// evaluates polynomial value at a particular x value (independent variable)
double polynomial::evaluate_at(double x) const
{
  double value = 0; // initialize value of polynomial at x to be 0
  for (int index = 0; index < coefficients.size(); index++) // for each term/x power
    {
      value += coefficients[index]*pow(x,coefficients.size()-index-1); // update the polynomical value with that term's value
    }
  return (value);
}

//finds initial bounds (for x) such that the polynomial value at the left bound is less than the polynomial value at the right bound, and ensures polynomial crosses the x axis within the bounds
void find_initial_bounds(const polynomial& poly, double& left, double& right)
{
  // throws error if the polynomial does not have an odd degree/power or if the left value is not less than the right value (at either bound)
  if (!(poly.is_odd() && left < right))
    {
      throw std::invalid_argument("Invalid initial bounds");
    }

  double leftval = poly.evaluate_at(left); // value at the left/lesser bound
  double rightval = poly.evaluate_at(right); // value at the right/higher bound

  while (leftval * rightval > 0) //loop to ensure that leftval < 0 and rightval >0; polynomial crosses 0
    { // increase the bound size
      left -=1;
      right += 1;
      // re-evaluate values at either bound
      leftval = poly.evaluate_at(left);
      rightval = poly.evaluate_at(right);
    }
}

// tightens bounds, while still maining pre-defined constraints
void move_bounds_closer( const polynomial& poly,double& left,double& right, bool trace)
{
  // assign/initialize values at either bound
  double leftval = poly.evaluate_at(left);
  double rightval = poly.evaluate_at(right);

  if (!(left < right && leftval * rightval <= 0)) //recheck/ensure conditions
    {
      throw std::invalid_argument("Invalid bounds");
    }

  double mid = (left + right) / 2; // midpoint x value
  double midval = poly.evaluate_at(mid); // polynomial value at midpoint

  if (midval * leftval <= 0) // midval is positive
    { //squeeze right bound in
      right = mid;
      rightval = midval;
    }
  else // midval is negative
    { // squeeze left bound in
      left = mid;
      leftval = midval;
    }
}
//finds the root/location for zero polynomial value
double find_zero( const polynomial& poly,double prec,bool trace)
{
  if (!poly.is_odd()) //recheck that polynomial is even
    {
      throw std::invalid_argument("Even-degree polynomial not supported");
    }

  double left = -10/* set initial left bound */;
  double right = 10/* set initial right bound */;

  find_initial_bounds(poly, left, right); // find the initial bound
  //using the middle value between the bounds as the zero point
  while (abs(poly.evaluate_at((left + right) / 2)) >= prec) // while the polynomial value is not within the range (+/- precision)
    {
      move_bounds_closer(poly, left, right, trace); // squeeze the bound tighter
    }

  // achieved the desired precision, find the xintercept/return intercept value
  double xintercept = (left + right) / 2;
  return xintercept;
}





