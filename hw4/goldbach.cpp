# include <iostream>
# include <vector>
using std::vector;
using std::cout;
using std::cin;

int generateP(int e, int bounds)
{
  vector <int> primes;
  int currentNum = 2;
  while (currentNum < e)
    {
      if (isprime(currentNum))
	{
	 primes.push_back;
	}
      currentNum ++;
    }
  pq(primes, e);
  return primes; 
}

bool pq(vector <int> primes, int e)
  for (int p::primes)
  {
    if isprime(e-p)
       cout << "The number " << e << "is" << p << "+" << q;
       break;
  }

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

int main()
{
  int bound;
  cout << "Enter a bound for the max value of an even number: ";
  cin >> bound;
  
  for (int e = 4; e <= bound; e ++2)
  {
    vector <int> primesM = generateP(e);
  }
}

