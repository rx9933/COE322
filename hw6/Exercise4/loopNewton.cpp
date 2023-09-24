/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2016-2023 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** newton.cpp : newton scalar example
 ****
 ****************************************************************/

#include <iostream>
using std::cin;
using std::cout;

#include <cmath>
#include <functional>

using std::cout;
using std::function;

double newton_root( function< double(double) > fn, function< double(double) > fnprime ) {
  double x{1.};
  while ( true ) {
    auto fx = fn(x);
    // cout << "f( " << x << " ) = " << fx << '\n';
    if (std::abs(fx)<1.e-10 ) break;
    x = x - fx/fnprime(x);
  }
  return x;
};

int main() {

  for (int n =2; n<=8; n++)
    {
      auto fn = [n] (double x ) { return x*x-n; };
      auto fnprime = [] (double x) {return 2*x;};
      cout << "sqrt(" <<n<< ") = " << newton_root(fn, fnprime) << '\n';
    }

  return 0;
}





