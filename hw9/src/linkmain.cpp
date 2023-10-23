
/*
Name: Arushi Sadam
UT EID: ars7724
TACC ID: a2097855
*/
// MAIN FILE

//include access to header file, standard input output, use of pointer
#include "linkshared.hpp"
#include <iostream>
using std::cin;
using std::cout;

#include <memory>
using std::make_shared;
using std::shared_ptr;

int main() { // inserts multiple elements and checks if values have been added, the lengths of the list after each addition, and other checks

  List mylist;
  cout << "Empty list has length: "
       << mylist.length() << '\n';
  cout << '\n';

  mylist.insert(3);
  cout << "After inserting 3 the length is: "
       << mylist.length() << '\n';
  if (mylist.contains_value(3))
    cout << "Indeed: contains 3" << '\n';
  else
    cout << "Hm. Should contain 3" << '\n';
  if (mylist.contains_value(4))
    cout << "Hm. Should not contain 4" << '\n';
  else
    cout << "Indeed: does not contain 4" << '\n';
  cout << '\n';

  mylist.insert(3);
  cout << "Inserting the same item gives length: "
       << mylist.length() << '\n';
  if (mylist.contains_value(3)) {
    cout << "Indeed: contains 3" << '\n';
    auto headnode = mylist.headnode();
    cout << "head node has value " << headnode->value()
         << " and count " << headnode->count() << '\n';
  } else
    cout << "Hm. Should contain 3" << '\n';
  cout << '\n';

    mylist.insert(2);
  cout << "Inserting 2 goes at the head;\nnow the length is: "
       << mylist.length() << '\n';
  if (mylist.contains_value(2))
    cout << "Indeed: contains 2" << '\n';
  else
    cout << "Hm. Should contain 2" << '\n';
  if (mylist.contains_value(3))
    cout << "Indeed: contains 3" << '\n';
  else
    cout << "Hm. Should contain 3" << '\n';
  cout << '\n';

  mylist.insert(6);
  cout << "Inserting 6 goes at the tail;\nnow the length is: "
       << mylist.length()
       << '\n';
  if (mylist.contains_value(6))
    cout << "Indeed: contains 6" << '\n';
  else
    cout << "Hm. Should contain 6" << '\n';
  if (mylist.contains_value(3))
    cout << "Indeed: contains 3" << '\n';
  else
    cout << "Hm. Should contain 3" << '\n';
  cout << '\n';

  mylist.insert(4);
  cout << "Inserting 4 goes in the middle;\nnow the length is: "
       << mylist.length()
       << '\n';
  if (mylist.contains_value(4))
    cout << "Indeed: contains 4" << '\n';
  else
    cout << "Hm. Should contain 4" << '\n';
  if (mylist.contains_value(3))
    cout << "Indeed: contains 3" << '\n';
  else
    cout << "Hm. Should contain 3" << '\n';
  cout << '\n';

  cout << "List has length: " << mylist.length() << '\n';
  cout << '\n';

  {
    cout << "Another check.\n";
    List mylist; // creates a new empty list
    for ( auto i : { 15,23,11,75,11,65,3} ) { // loops through lists, and adds each element
      cout << "insert: " << i << '\n';
      mylist.insert(i);
    }
    mylist.print(); // outputs the list
  }

  {
    cout << "Enter a list of input numbers: "; //adding this section; directs user on how to input numbers 
    int nextinput; // initialize the input type
    List mylist; // create new list
    while(true) // until user enters 0
    {
        cin>>nextinput;  // get the next input value
        if(nextinput!=0) // if it is not 0
        {
            mylist.insert(nextinput); // add value
            mylist.formattedPrint(); // output list in a formatted/specific manner
        }
        else // input 0
        {
            break; // exit loop
        }
    }
  }
  return 0;
}