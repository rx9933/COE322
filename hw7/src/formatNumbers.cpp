// Name: Arushi Sadam
// UT EID: ars7724
// TACC Username: a2097855

//Pupose: output a 16 x 16 board of numbers (from 0 to 255 in base 10) in base 16 (hexadecimal) 

//include standard input output streams (to output grid)
#include <iostream>
using std::cout;
using std::ostream;

// include string usage (each hex number is written in a string)
#include <string>
using std::string;

// include formatting library for aligned grid, using fmt format and print functions
#include <fmt/format.h>
using fmt::format,fmt::print;

// convert the input integer to a 2-digit hexadecimal string
string to_hex(int number) {
  return format("{:02x}", number); // (2-1) = 1 zero followed by lower case number (lower case x)
}

// builds 16x16 grid of hex numbers 
int main() 
{
  for (int row = 0; row < 16; ++row) { // iterate over each row of grid
    for (int col = 0; col < 16; ++col) { // iterate over each column of grid
      int number = row * 16 + col; // calculate number in base 10 based on position; row represents ones place * col represents tens place
      string hex_number = to_hex(number); // convert base 10 number to hexadecimal number of type string
      print("{:<3}", hex_number); // number of spaces between the start of each hex number (includes length of each hex number = 2 + 1 space = 3)
    }
    print("\n"); // add a new line after each row of numbers
  }

  return 0;
}
