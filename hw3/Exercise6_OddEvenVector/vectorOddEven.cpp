/*
Name: Arushi Sadam
UT EID: ars7724
TACC username: a2097855
*/

/* Purpose: Seperate an input vector of integers into two construct vectors: one with all the odd integers of the input vector and one with all the even integers of the input vector. 
*/

//using standard input-output stream, vectors, and strings
# include <iostream>
# include <vector>
# include <string>

using std::vector;// using standard vectors
using std::string;// using standard string function
using std::cout; // using standard character output
using std::cin;// using standard character input

// sorting function that creates two vectors (one with odd ints and the other with even ints) out of the input vector
void oddEvenFunc(vector <int> &inputV) 
// &inputV = passing the input numbers vector by reference. Allows original vector in the main code to remain unchanged; this is not a necessary step for this program.

{ //initializing vectors of integers for the odd numbers and for the even numbers
 vector<int>oddNum;
 vector<int>evenNum;

 for (int i = 0; i < inputV.size(); i++) // loop that checks each number in the input vector; i represents the index in the input vector
   {
     if (inputV[i] % 2 == 0) // if the integer value at index i is even
       {
	 evenNum.push_back(inputV[i]); // add the even integer to the even numbers vector
       }
     else // integer value at index i is odd
       {
	 oddNum.push_back(inputV[i]); // add the odd integer to the odd numbers vector
       }
   }
 cout << "Odd numbers in input vector: "; // output description for odd numbers vector
 for (int i = 0; i < oddNum.size(); i++) // loops through each index (i) in odd numbers vector; starts with the first index of the vector
   {
     cout << oddNum[i]; // output the value in the odd numbers vector corresponding with the index
     if (i != oddNum.size()-1) //as long as not at the last number/value of the vector
       cout << ", "; // add comma (between subsequent values of the odd number vector output to screen)
   }
 cout << "\nEven numbers in input vector: "; // output description for even numbers vector
 for (int i =0; i < evenNum.size(); i++) // loops through each index (i) in even numbers vector; starts with the first index of the vector
   {
     cout << evenNum[i]; // output the value in the even numbers vector corresponding with the index
     if (i != evenNum.size()-1) // as long as not at the last number/value of the vector
       cout << ", "; // add comma (between subsequent values of the even number vector output to screen)
   }
 cout << "\n"; // add a new line
}


int main() //main function that initializes the input vector and calls the function that sorts the numbers into odd or even groups.
{
  vector <int> inputV; // initialize vector of input integers
  cout << "Enter numbers as the input vector. Seperate each number with an ENTER. To stop entry, press a non-integer key. \n"; // instruction sentence, output
  int inputNum; // initialize variable for input numbers
  while (cin >> inputNum) // while input numbers are provided, remain in this loop and append to vector of input integers
   {
     inputV.push_back(inputNum); // add each input number to vector of input integers
   }

  oddEvenFunc(inputV); //call/apply the odd/even sorting function to the input number vector 
}
