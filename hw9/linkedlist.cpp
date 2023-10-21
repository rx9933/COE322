l/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2017-2023 Victor Eijkhout eijkhout@tacc.utexas.edu
 **** 
 **** link.cxx : linked list using shared smart pointers
 ****
 ****************************************************************/

#include <cmath>

#include <iostream>
using std::cin;
using std::cout;

#include <memory>
using std::make_shared;
using std::shared_ptr;

#include <vector>
using std::vector;

#include <cassert>

class Node; // forward definition
class List {
private:
  shared_ptr<Node> head{nullptr};
public:
  List() {};
  auto headnode() { return head; };
  void insert(int value);
  int length();
  int length_iterative();
  bool contains_value(int v);
  void print();
};

class Node {
private:
  int datavalue{0},datacount{0};
  shared_ptr<Node> next{nullptr};
public:
  Node() {};
  Node(int value,shared_ptr<Node> next=nullptr)
    : datavalue(value),datacount(1),next(next) {};
  int value() {
    return datavalue; };
  auto nextnode() {
    return next; };
  int length();
  // This One Is New
  bool contains_value(int v);
  int count() {
    return datacount; };
  bool has_next() {
    return next!=nullptr; };
  void insert(int value);
  void print();
  
   // New public method to access `next`
  shared_ptr<Node> get_next() {
    return next;
  }

};

int main() {

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
  ///////////////////////////////////////////////////
#if 0
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
    List mylist;
    for ( auto i : { 15,23,11,75,11,65,3} ) {
      cout << "insert: " << i << '\n';
      mylist.insert(i);
    }
    mylist.print();
  }
#endif

  return 0;
}

/*
 * Compute the length of a list recursively
 * See below for an iterative solution
 */
int List::length() {
  int count = 0;
  if (head==nullptr)
    return 0;
  else
    return head->length();
};

int Node::length() {
  if (!has_next())
    return 1;
  else
    return 1+next->length();
};

/*
 * Iterative alternative
 * to recursive computation
 */
int List::length_iterative() {
  int count = 0;
  if (head!=nullptr) {
    auto current_node = head;
    while (current_node->has_next()) {
      current_node = current_node->nextnode(); count += 1;
    }
  }
  return count;
};

/*
 * Auxiliary functions
 */

void List::insert(int value) {
  if (head == nullptr) {
    head = make_shared<Node>(value);
  } else {
    shared_ptr<Node> current = head;
    shared_ptr<Node> previous = nullptr;

    // Find the correct position to insert the new node
    while (current && value >= current->value()) {
      previous = current;
      current = current->get_next();
    }

    // Create a new node
    shared_ptr<Node> newNode = make_shared<Node>(value);

    if (!previous) {
      // Insert at the beginning
      
      // Insert in the middle or at the end
      
    }
  }
}

bool List::contains_value( int value ) {
  if (head==nullptr)
    return false; // no pointer, so no value
  else
    return head->contains_value(value); //evaluates recursively if value is in linked list, return boolean
};

bool Node::contains_value( int value) {
  if (datavalue==value)
    {
    // if I contain this value, true
      datacount++;
      return true;
    }
  else if (next==nullptr)
    {
      // else, 1. if not tail: false
      return false;
    }
  else
    // 2. return: my tail contains this value
    {
      return next->contains_value(value);
    }
};

// ESC > : go to end of file
// ESC < : go to beginning of file
// C-v : one screen down
// ESC v : one screen up

void List::insert(int value) {
  if (head == nullptr) {
    head = std::make_shared<Node>(value);
  } else {
    head = head->insert(value);
  }
}

void Node::print() {
  cout << datavalue << ":" << datacount;
  if (has_next()) {
    cout << ", "; next->print();
  }
};

void List::print() {
  cout << "List:";
  if (head!=nullptr)
    cout << " => "; head->print();
  cout << '\n';
};

/*
 * The homework stuff
 */

