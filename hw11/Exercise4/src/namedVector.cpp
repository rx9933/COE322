/*
  Name: Arushi Sadam
  UT EID: ars7724
  TACC ID: a2097855
 */
//using standard input/output streams, vectors, and strings
#include <iostream>
using std::cin;
using std::cout;

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

//creates an instance of namedvector, and outputs: the name, the size, and the first value of the vector
int main() {
  namedvector<float> fivetemp("five",5); // creats a vector of floats with size 5 and name "five"
  cout << fivetemp.name() 
       << ": "
       << fivetemp.size() << '\n'; // output name/size of vector fivetemp
  cout << "at zero: "
       << fivetemp.at(0) << '\n'; // output the fist value in the vector, values enclosed are initialized at 0

}
