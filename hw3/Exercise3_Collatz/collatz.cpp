# include <iostream>
# include <vector>
using std::cout;
using std::cin;
using std::vector;

int cFunction(int n)
{
 int sequenceL = 0;
 while (!(n==1))
 {
   sequenceL += 1;
   if (n%2 == 0)
   {
     n = n/2;
   }
   else
   {
     n = 3*n+1;
   }
 }
 return sequenceL; 
}

void printList(vector<int> startingNums)
{
 for (int j = 0; j != startingNums.size(); j++)
 {
 cout << startingNums[j];
 if (j != startingNums.size()-1)
   {
     cout << ", ";
   }
 }
}

int main()
{
 int maxSequenceL = -1; // initialize at non-possible length, so n=1 has 0 iterations
 cout << "Starting number sequence: ";
 vector<int> startingNums{};
 for (int n = 1; n <= 1000; n++)
 {
  int currentSequenceL = cFunction(n);	
  if (currentSequenceL > maxSequenceL)
  {
    maxSequenceL = currentSequenceL;
    startingNums.push_back(n);  
  }
 }
 printList(startingNums);
 cout << "\n";
}
