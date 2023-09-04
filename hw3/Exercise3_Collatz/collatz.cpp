/*
Name: Arushi Sadam
UT EID: ars7724
TACC username: a2097855
*/

//Purpose: Try values n = 1,2,.....1000 to find the values that lead to the longest sequence through the Collatz algorithm. Each time a sequence is longer than a previous maximum, the n value (starting number) is output.

//using standard input-output stream, vectors
# include <iostream>
# include <vector>
using std::cout; // using standard character output
using std::cin; // using standard character input
using std::vector; // using standard vectors

int cFunction(int n) // function takes in integer n, a starting number, and evaluates the length of the resulting collatz sequence for that number
{
 int sequenceL = 0; // initialize sequence length to 0
 while (!(n==1)) // as long as the number is not transformed to 1, through a series of collatz iterations, continue iterations
 {
   sequenceL += 1; // increment number of iterations
   // collatz sequence algorithm logic
   if (n%2 == 0) // if currently even number
   {
     n = n/2; // next number is half of the original; reassign current number value (n value)
   }
   else // if currently odd number
   {
     n = 3*n+1; // next number is thrice the original plus 1; reassign current number value (n value)
   }
 }
 return sequenceL; // return the final sequence length for the particular starting number (which was the input) to the main function
}

void printList(vector<int> startingNums) // void function that prints the elements of vector startingNums with commas between values, creates a copy of startingNums vector
{
  for (int j = 0; j != startingNums.size(); j++) //j represents each starting number index; continue interation of the for loop for every index in the input vector. .size() gives the length of the input vector
 {
   cout << startingNums[j]; // print the value of the vector at a particular index
   if (j != startingNums.size()-1) // if not the last element in the input vector (not at last index of input vector)
   {
     cout << ", "; // add comma between values
   }
 }
}

int main()
{
 int maxSequenceL = -1; // initialize at non-possible length, so n=1 has 0 iterations and can appear on list as the first number
 cout << "Starting number sequence: ";
 vector<int> startingNums{}; // initialize vector of all the starting numbers that result in the longest sequence of collatz numbers
 for (int n = 1; n <= 1000; n++) // loop through 1000 starting numbers starting at 1
 {
  int currentSequenceL = cFunction(n);	// cFunction evaluates length of the current sequence, with the starting number n
  if (currentSequenceL > maxSequenceL) // if the length of the current sequence is larger than all the previous sequence lengths
  {
    maxSequenceL = currentSequenceL; // re-assign largest sequence length
    startingNums.push_back(n);   // add the starting number n to the vector of starting numbers
  }
 }
 // after checking first 1000 starting numbers, print out the existing vector of numbers with the longest sequence lengths
 printList(startingNums); // printList is a void function that prints each integer in a vector of integers with a comma between the values
 cout << "\n"; // end with a new line
}
