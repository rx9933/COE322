/*
Name: Arushi Sadam
UT EID: ars7724
TACC Account Number: a2097855
*/

// using standard input output streams, math for absolute value (abs), and function stream for using a lambda value as a function parameter
#include <iostream>
#include <cmath>
#include <functional>

using std::function;
using std::cout;
using std::cin;

// function to find the root of a input integer using the Newton-Raphson method
double newton_root(function <double(double)> f) { // takes function f as input
  double root{1.}; 
  double h{1e-6}; // Finite difference step size
  while (true) { // re-evaluate the root, until sufficiently cloose to actual root value (within threshold size)
    auto froot = f(root); // evaluate function at current root value
    if (std::abs(froot) < 1.e-10) break;// check if absolute value of f(root) is below threshold value, exit loop if within threshold
    float gradient = (f(root + h) - f(root)) / h; //gradient or slope at point root
    root = root - froot / gradient; // update root using Newton method
  }
  return root; 
}

//initializes input integer, calls function to evaluate root, and outputs root
int main() {
  int integer;
  cout << "input an integer to find the root of: ";
  cin >> integer; // input integer, to find the root of
  auto f = [integer] (double x) { return x * x - integer; }; // define function f(x) = x^2 - integer, captures integer
  double root = newton_root(f); // call function to find root
  cout << "The root of this number is " << root << '\n'; // output root value
  return 0;
}
