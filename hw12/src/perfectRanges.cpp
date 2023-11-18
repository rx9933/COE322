/*
  Name: Arushi Sadam
  UT EID: ars7724
  TACC ID: a2097855
 */

// including modules for standard input/output streams, math for square root function, and range/v3 for using ranges--functions views, iota, etc.
#include <iostream>
using std::cout; 
#include <math.h>
#include <range/v3/all.hpp>

//function checks if the inputted number is perfect
bool is_perfect(int num) {
  int sum_of_divisors = 0; // initialize the sum of the divisors of the input number
  auto divisors = ranges::views::iota(1, static_cast<int>(std::sqrt(num)) + 1)  // range from 1 to sqrt of input num. +1 ensures including the int value of the root, in case it is also a divisor
    | ranges::views::filter([num, &sum_of_divisors](int x) // pipe that through a filter that checks if the sum of the divisors of the num = num
      {
	if (num % x == 0) { // is divisor
	  sum_of_divisors += x; // add the divisor to total sum
	  sum_of_divisors += num/x; // add the corresponding multiple (other divisor) to sum
      }
	return true;
    });
  sum_of_divisors -= num; // remove the last divisor (num itself) from sum of divisors
  ranges::for_each(divisors, [](int) {}); // loops through each divisor

  return sum_of_divisors == num; //return boolean, if the number is perfect
}

int main() {
  auto perfect_numbers = ranges::views::iota(2,10000) | ranges::views::filter(is_perfect) | ranges::views::take(4); // check for perfect numbers between 2 and 10,000, filter per is_perfect function logic, then use only the first 4 perfect numbers

  cout << "Perfect numbers: ";
  ranges::for_each(perfect_numbers, [](int num) {  //loop through
      cout << num << " "; // and output the perfect numbers
    });
  cout << '\n';

  return 0;
}
