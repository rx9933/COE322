/* 
Name: Arushi Sadam
UT EID: ars7724
TACC username: a2097855
*/

# include <iostream>
# include <cmath>

using std :: cout;
using std :: cin;

class primegenerator
{
private:
  int currentNum;
  int primeNums; // number of prime numbers that have been found 

public:
  primegenerator() : currentNum(1), primeNums(0) {};
  int number_of_primes_found()
  {
    //    cout << currentNum << "is a prime \n" ;
    primeNums ++;
    return primeNums;
  }
  
  bool isprime(int num)
  {
    bool isNumPrime = true;
    if (num <=1)
      isNumPrime = false;
    for (int divisor = 2; divisor <= sqrt(num); divisor ++)
      {
	if (num % divisor == 0)
	  isNumPrime = false; // not a prime number
          break;

      }
     return isNumPrime; 
  }
  
  int nextprime()
  {
    currentNum ++;  
    while (!isprime(currentNum))
      {
	currentNum ++;
      }
      return currentNum;
      
  }
};

int main()
{
  cout << "Enter the number of primes you want: "; 
  int nPrimes;
  cin >> nPrimes; // maximum number of prime numbers, set by user 
  primegenerator sequence;
  while(sequence.number_of_primes_found() < nPrimes)
    {
      int number = sequence.nextprime();
      cout << "Number " << number << " is prime" << "\n";
    }
}
