/*
Name: Arushi Sadam
UT EID: ars7724
TACC Account Number: a2097855
 */

//using standard input output streams and vector
# include <iostream>
# include <vector>
# include <math.h> 
using std::vector;
using std::cout;
using std::cin;

//checks if num is divisible by div
bool divides(int div, int num)
{
  bool divides{false};
  if (num%div == 0)
    {
      divides = true;
    }
  return divides;
}

//checks "primeness" of input number (testNum)
bool isprime(int testNum)
{
  bool isnotprime{false};
  for (int divisor = 2; divisor <= sqrt(testNum); divisor ++)
    {
      isnotprime = isnotprime or divides(divisor, testNum);
    }
  return not isnotprime;
} 

//checks + outputs the two primes (q and p) that can be averaged to find a middle prime, r
void pq(int r) // middle prime (avg of q and p)
{
  for (int dx = 1; dx <= r-2; dx ++)
    {
      int q = r+dx; // upper prime in sum
      int p = r-dx; // lower prime in sum
      if (isprime(q) && isprime(p))
        {
          cout << r << " = (" << p << " + " << q << ") / 2 \n";
          break;
        }
    }
}

//generates a vector of prime numbers from 2 to the max prime within inputted bounds
vector <int> generateP(int bound)
{
  vector <int> primes;
  int currentNum = 2;
  while (currentNum <=bound)
    {
      if (isprime(currentNum))
        {
          primes.push_back(currentNum);
        }
      currentNum ++;
    }
  return primes;
}

//initializes variables + calls function to (check+output) results
int main()
{
  int bound;
  cout << "Enter a bound for the max value of primes to check: ";
  cin >> bound;

  vector <int> primes = generateP(bound); // list of primes
  for (int r: primes) // r is the avg prime (middle number), checks all primes from 2 to max bounds
    {
      pq(r); // function that checks if  r is the average of two primes equidistant from r (checks corollary) + outputs the 3 primes
    }
}





















