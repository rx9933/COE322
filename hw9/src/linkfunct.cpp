/*
Name: Arushi Sadam
UT EID: ars7724
TACC ID: a2097855
*/
// FUNCTIONS/IMPLEMENTATION FILE

#include "linkshared.hpp" // link functions to header

int List::length() { // calculates length of list
  int count = 0; // initialize count (length) to 0
  if (head==nullptr) // if empty list, length is 0
    return 0;
  else
    return head->length(); // if non-empty list go to node length function
};

int Node::length() { // calculates length of list (as long as not empty)
  if (!has_next()) // no more elements after this
    return 1; //add 1 more and stop
  else
    return 1+next->length(); // repeat loop -- call list length function
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

void List::print() { // print elements
  cout << "List:"; // print "List" initially at start of list output
  if (head!=nullptr) // as long as non-empty list
    cout << " => "; head->print(); // call the print function (of class node) to output value of head
  cout << '\n';
};

void Node::print() { // print elements
  cout << datavalue << ":" << datacount;
  if (has_next()) { // if next element in list exists
    cout << ", "; next->print(); // ... add a comma, and call the List print function to repeat cycle
  }
};

void List::formattedPrint() { // prints elements in particular fomrmat : "List: -10, 1, 2, 3, 3, 9"
  auto currentNode = head; // initialize currentNode pointer to first element
  cout << "List: ";
  while (currentNode) { // while still Node exists
      cout << currentNode->value(); // print currentNode value
    if (currentNode->has_next()) { // if another element exist 
      cout << ", "; // ... add a comma
    }
    currentNode = currentNode->nextnode(); // move currentNode to point to the nextNode; if exists, iterate through while loop again
  }
  cout << "\n";
}

/*
 * The homework stuff
 */

void List::insert( int value ) // insert value into list
{ 
  if (head==nullptr) // if empty list
  {
    head = make_shared<Node>(value, nullptr); // head points to inputted value
    cout<< "data start 0 "<<head->count()<< " value " << value << "\n"; 
  }
  else // if non-empty list
  {
    shared_ptr<Node> currentNode = head; // initialize currentNode to head -- point to first element
    if (value < currentNode->value()) // input value is smallest in the list; goes to the front/head
    {
        auto newNode = make_shared<Node>(value, currentNode); // use constructor to create a newNode that has value the input value, where the next node is currentNode (=head)
        head = newNode; // move head to point to new first value in list
    }
    else // input value goes in the middle or end of list
    {
        bool inserted = false; // flag checks if input value has been inserted into list
        while (currentNode->has_next()) // loop finds location for insertion; loops through list until no more next nodes 
        {
            if (value<=currentNode->nextnode()->value()) // if input is less than nextNode value (inevitably greater than currentNode), then insert here
            { // insert between currentNode and currrentNode's next node
              auto newNode = make_shared<Node>(value, currentNode->nextnode()); // create a newNode with value the input value and pointing to the nextNode after currentNode
              currentNode->setnextnode(newNode); // change currentNode to point to the newNode that is created
              inserted = true; // change flag
              break; // exit loop, insertion complete
            }
            currentNode=currentNode->nextnode(); // have not exited loop, so move pointer and check the next node
        }

        if (inserted==false) // input value is largest in list; goes at tail/end
        { // after currentNode, which is now at end
            auto newNode = make_shared<Node>(value, nullptr); // create a newNode with value the input value and pointing to null/empty
            currentNode->setnextnode(newNode); // change currentNode to point to the newNode that is created
        }
    }
  }
  cout<< "data start "<<head->count()<< " value " << value << "\n"; 
  head->insert(value); 
};

void Node::insert(int value) // updating datacounts
{
if (datavalue == value) // element is repeated
 {
  if (has_next()) // as long as not at end of list
    {
    if(nextnode()->value() == datavalue) // check if next node has the same value
        {datacount ++;} // ... if so, update the datacount
    nextnode()->insert(value);  //repeat loop for nextnode 
    }
  }
}

void Node::setnextnode(shared_ptr<Node> newNode) // sets pointer to next node (require this function from class Node to acess next pointer)
{
  next=newNode; // set the next pointer to the new/created Node 
}

bool List::contains_value( int value ) { // checks if value in list
  if (head==nullptr) // empty list, value not in list
    return false;
  else
    return head->contains_value(value); // call contains_value function in Node class to check if the head has the value
};

bool Node::contains_value( int value) {
  if (datavalue==value) // value already in list
  {
    // if I contain this value, true
    return true;
  }
  else if (next==nullptr) // only one value, not tail so false
  {
    // else, 1. if not tail: false
    return false;
  }
  else // tail must contain value, check if the next value has the value
    {//       2. return: my tail contains this value
    return next->contains_value(value); // repeat loop/cycle by calling the contains_value function from List class
    }
};