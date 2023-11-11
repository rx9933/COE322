/*
  Name: Arushi Sadam
  UT EID: ars7724
  TACC ID: a2097855
*/

//using standard input/output streams, vectors, and strings
#include <iostream>
using std:: cout;
#include <vector>
#include <string>

//class namedvector inherits from the standard vector class
template <typename T> // use templates to keep the data type within the vector as variable
class namedvector : public std::vector<T> {
private:
  std::string _name; // private member that stores the name of the vector

public:
  namedvector(std::string n, int s)
    : _name(n), std::vector<T>(s) {}; //constructor takes the name & size to initialize the vector

  auto name() const {
    return _name; // function to get/retrieve name of vector
  }
};

namespace geo { // create new namespace with same functionality as class namedvector
  template <typename T>
  class vector : public namedvector<T> { // inherits functions from class namedvector
  public:
    vector(std::string n, int s) : namedvector<T>(n, s) {} // constructor initializes vector with the namedvector constructor (same size/arguments) 
    // n represents name, s represents size, T (from template) allows data types that are stored to be unspecified
  };
}

int main() {
  namedvector<float> fivetemp("five",5); // creats a vector of floats with size 5 and name "five"
  cout << fivetemp.name()
       << ": "
       << fivetemp.size() << '\n'; // output name/size of vector fivetemp
  cout << "at zero: "
       << fivetemp.at(0) << '\n'; // output the fist value in the vector, values enclosed are initialized at 0

  using namespace geo;
  geo::vector<float> float4("four", 4); // creates a vector of floats with size 4 and name "four", using the geo namespace class vector
  std::cout << float4.name() << '\n'; // output the name of the vector
  float4[1] = 3.14; // assigns the 2nd element (index 1) of the vector to be a float of 3.14
  std::cout << float4.at(1) << '\n'; // output vector's stored value at the 2nd element

  geo::vector<std::string> string3("three", 3); // creates a vector of strings with size 3 and name "three", using the geo namespace class vector
  string3.at(2) = "abc"; // assigns the 2nd index/third element of the vector to be a string, "abc"
  std::cout << string3[2] << '\n'; // outputs the value stored in the third element of the three vector
  return 0;
}

