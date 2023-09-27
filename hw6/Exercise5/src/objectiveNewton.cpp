/*
Name: Arushi Sadam
UT EID: ars7724
TACC Account Number: a2097855
*/

// using standard input output streams, math for absolute value (abs), function stream for using a lambda value as a function parameter,
// cxxopts to input integer (to find root of) from command line, string to convert input to integer
#include <iostream>
#include <cmath>
#include <functional>
#include "cxxopts.hpp"
#include <string>

using std::function;
using std::cout;
using std::cin;

// function to find the root of a input integer using the Newton-Raphson method
double newton_root(function <double(double)> f) { // takes function f as input
  double root{1.}; 
  double h{1e-6}; // Finite difference step size
  const int maxIterations = 1000;
  int iterationNumber;
  for (iterationNumber = 0; iterationNumber < maxIterations; iterationNumber ++) // break loop if Newton's method does not converge quickly enough.
    {
      auto froot = f(root); // evaluate function at current root value
      if (std::abs(froot) < 1.e-10) break;// check if absolute value of f(root) is below threshold value, exit loop if within threshold
      float gradient = (f(root + h) - f(root)) / h; //gradient or slope at point root
      root = root - froot / gradient; // update root using Newton method
    }

  if (iterationNumber == maxIterations-1)
    {
      cout << "root did not converge quickly enough";
    }
  return root; 
}

//initializes input integer, calls function to evaluate root, and outputs root
int main(int argc, char* argv[]) {
  if (argc == 1)
    {
      cout << "did not input any arguments for integer value \n";
      return 1; //error
    }
  float inputNum = atof(argv[1]); // input integer, to find the root of
  auto f = [inputNum] (double x) { return x * x - inputNum; }; // define function f(x) = x^2 - integer, captures integer
  double root = newton_root(f); // call function to find root
  cout << "The root of this number is " << root << '\n'; // output root value
  return 0;
}
