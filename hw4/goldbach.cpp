# include <iostream>
# include <vector>
using std::vector;
using std::cout;
using std::cin;


bool isprime(int testNum)
{
  bool isNumPrime = true;
  if (testNum <=1)
    isNumPrime = false;
  for (int divisor = 2; divisor <= testNum/2; divisor ++)
    {
      if (testNum % divisor == 0)
	{
          isNumPrime = false; // not a prime number
          break;
	}
    }
  return isNumPrime;
}

void pq(vector <int> primes, int e)
  {
  for (int p:primes)
    {
    int q = e-p;
    if (isprime(q))
      {
       cout << "The number " << e << " is " << p << " + " << q << "\n";
       break;
      }
    }
  }

void generateP(int e, int bound)
{
  vector <int> primes;
  int currentNum = 2;
  while (currentNum <=e)
    {
      if (isprime(currentNum))
	{
	 primes.push_back(currentNum);
	}
      currentNum ++;
    }
  pq(primes, e);
  // return primes; 
}


int main()
{
  int bound;
  cout << "Enter a bound for the max value of an even number: ";
  cin >> bound;
  
  for (int e = 4; e <= bound; e+=2)
  {
    generateP(e, bound);
  }
}

