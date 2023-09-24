#include <iostream>
#include <cmath>
#include <functional>

using std::function;
using std::cout;

double newton_root(function <double(double)> f, function <double(double, double)>gradient) {
  double x{1.};
  double h{1e-6}; // Finite difference step size
  while (true) {
    auto fx = f(x);
    if (std::abs(fx) < 1.e-10) break;
    float df = gradient(x,h); // Approximate derivative using finite difference
    x = x - fx / df;
  }
  return x;
}

int main() {
  for (int n = 2; n <= 8; ++n)
    {
      auto fn = [n] (double x) { return x * x - n; };
      auto gradient = [fn] (double x, double h) { return (fn(x + h) - fn(x)) / h; };
      double root = newton_root(fn, gradient);
      cout << "sqrt(" << n << ") = " << root << '\n';
    }
  return 0;
}
