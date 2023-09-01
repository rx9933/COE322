# include <iostream>
# include <vector>
# include <string>
using std::vector;
using std::string;
using std::cout;
using std::cin;

void oddEvenFunc(vector <int> &inputV)
{
 vector<int>oddNum;
 vector<int>evenNum;

 for (int i = 0; i < inputV.size(); i++)
   {
     if (inputV[i] % 2 == 0)
       {
  	evenNum.push_back(inputV[i]);
       }
     else
       {
        oddNum.push_back(inputV[i]);
       }
   }
 cout << "Odd numbers in input vector: ";
 for (int i = 0; i < oddNum.size(); i++)
   {
     cout << oddNum[i];
     if (i != oddNum.size()-1)
       cout << ", ";
   }
 cout << "\nEven numbers in input vector: ";
 for (int i =0; i < evenNum.size(); i++)
   {
     cout << evenNum[i];
     if (i != evenNum.size()-1)
       cout << ", ";
   }
 cout << "\n";
}


int main()
{
   vector <int> inputV; 
   cout << "Enter numbers as the input vector. Seperate each number with an ENTER. To stop entry, press a non-integer key. \n";
   int inputNum;
   while (cin >> inputNum)
   {
   inputV.push_back(inputNum);
   }

   oddEvenFunc(inputV);
}
