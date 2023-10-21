/*
Name: Arushi Sadam
UT EID: ars7724
TACC Account Number: a2097855
*/

//using standard input output streams, math for absolute value, and functions for inputting lambda values for functions
#include <iostream>
using std::cin;
using std::cout;

#include <cmath>
#include <functional>
using std::function;

//function to find the root of an input integer using the Newton-Raphson method
double newton_root( function< double(double) > finputnum, function< double(double) > fnprime ) { // takes functions fn and fnprime as parameters
  double root{1.};
  while (true) { // re-evaluate the root, until sufficiently cloose to actual root value (within threshold size)
    auto froot = finputnum(root); // evaluate function at current root value
    if (std::abs(froot) < 1.e-10) break;// check if absolute value of f(x) is below threshold value, exit loop if within threshold
    root = root - froot/fnprime(root);
  }
  return root;
};

//initializes input integers, calls function to evaluate each root, and outputs each root
int main() {
  for (int inputnum =2; inputnum<=8; inputnum++) //loop through multiple inputs
    {
      auto finputnum = [inputnum] (double x) { return x*x-inputnum; }; // define function f(x) = x^2 - inputnum
      auto fnprime = [] (double x) {return 2*x;}; // define gradient/slope function f'(x) = 2x
      cout << "sqrt(" << inputnum << ") = " << newton_root(finputnum, fnprime) << '\n'; //call newton_root and output each root
    }
  return 0;
}




