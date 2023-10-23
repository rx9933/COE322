// using standard input, output streams
#include <iostream>
using std::cin;
using std::cout;
//using shared pointers
#include <memory>
using std::make_shared;
using std::shared_ptr;


class Node; // forward definition
class List { 
private:
  shared_ptr<Node> head{nullptr}; // pointer to head; initialize as null
public:
  List() {}; // default
  auto headnode() { return head; };
  void insert(int value); // function to insert a value into list
  int length(); // finds length of list
  int length_iterative(); // iterative length counting function, not used
  bool contains_value(int v); // checks if the list contains a value
  void print(); // output list
  void formattedPrint(); // adding this function; output list in a particular format -- each element is comma seperated 
};

class Node {
private:
  int datavalue{0},datacount{0};
  shared_ptr<Node> next{nullptr};

public:
  Node() {}; // default
  Node(int value,shared_ptr<Node> next=nullptr)
    : datavalue(value),datacount(1),next(next) {}; // initialize values
  int value() {
    return datavalue; }; // returns the value 
  auto nextnode() {
    return next; }; // returns pointer tot he next node
  void setnextnode(shared_ptr<Node> newNode); // adding this function; used to assign pointer ot the next node
  int length(); // computes length of list
  bool contains_value(int v); // checks if value is in list
  int count() {
    return datacount; }; // returns the count/number of occurences
  void formattedPrint(); // adding this function; as above, used in formatting output
  bool has_next() { // checks if next node exits
    return next!=nullptr; };
  void insert(int value); // used to insert a value into list
  void print(); // standard output/print
};
