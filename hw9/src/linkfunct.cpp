#include "linkshared.hpp"

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

void List::formattedPrint() {
  auto currentNode = head;
  cout << "List: ";
  while (currentNode) {
    cout << currentNode->value();
    if (currentNode->has_next()) {
      cout << ", ";
    }
    currentNode = currentNode->nextnode();
  }
  cout << "\n";
}

/*
 * The homework stuff
 */

void List::insert( int value ) 
{
  if (head==nullptr) 
  {
    head = make_shared<Node>(value);
  }
  else
  {
    shared_ptr<Node> currentNode = head;
    bool inserted = false; 

    // 1st value in list
    if (value < currentNode->value())
    {
        auto newNode = make_shared<Node>(value, currentNode);
        head = newNode; 
    }
    else
    {
        bool inserted = false; // for middle
        while (currentNode->has_next()) 
        {
            if (value<currentNode->nextnode()->value())
            {
            auto newNode = make_shared<Node>(value, currentNode->nextnode());
            currentNode->setnextnode(newNode); 
            inserted = true;
            break;
            }
            currentNode=currentNode->nextnode();
        }

        if (inserted==false) // last value in lsit
        {
            auto newNode = make_shared<Node>(value, nullptr);
            currentNode->setnextnode(newNode);
        }
    }
  }
};

void Node::setnextnode(shared_ptr<Node> newNode)
{
  next=newNode;
}

bool List::contains_value( int value ) {
  if (head==nullptr) 
    return false;
  else
    return head->contains_value(value);
};

bool Node::contains_value( int value) {
  if (datavalue==value) 
    // if I contain this value, true
    return true;
  else if (next==nullptr)
    // else, 1. if not tail: false
    return false;
  else
    //       2. return: my tail contains this value
    return next->contains_value(value);
};