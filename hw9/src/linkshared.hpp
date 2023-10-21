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
  void formattedPrint(); // adding this function
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
  void setnextnode(shared_ptr<Node> newNode); // adding this function
  int length();
  bool contains_value(int v);
  int count() {
    return datacount; };
  void formattedPrint(); // adding this function
  bool has_next() {
    return next!=nullptr; };
  void insert(int value);
  void print();
};
