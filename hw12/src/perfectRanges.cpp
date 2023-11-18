#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <math.h>
#include <range/v3/all.hpp>

bool is_perfect(int num) {
  int sum_of_divisors = 0;

  auto divisors = ranges::views::iota(1, (int)sqrt(num)+1) | ranges::views::filter([num, &sum_of_divisors](int x) {
      if (num % x == 0) {
	sum_of_divisors += x;
	sum_of_divisors += num/x;
      }
      return true;
    });
  sum_of_divisors -= num;
  ranges::for_each(divisors, [](int) {});

  return sum_of_divisors == num;
}

int main() {
  auto perfect_numbers = ranges::views::iota(2,10000) | ranges::views::filter(is_perfect) | ranges::views::take(4);

  std::cout << "Perfect numbers: ";
  ranges::for_each(perfect_numbers, [](int num) {
      std::cout << num << " ";
    });
  std::cout << '\n';

  return 0;
}
