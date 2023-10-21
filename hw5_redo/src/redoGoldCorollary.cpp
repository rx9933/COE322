/*
//this assignment is being submitted by Arushi, and is done in collaboration with Hongseok. We are not submitting the same code, but our assignments do share some simillarities.
Name: Arushi Sadam, Hongseok Kim
UT EID: ars7724, hk24772
TACC Username: a2097855, inb05141
*/

// logic: for all primes greater than 4, there exists two primes that average to the original prime. These 2 primes are equidistant from the original prim// This code checks for the prime numbers until 100. Adjust the variable maxR in the main class to check for more or less prime numbers.


//using standard input-output stream
# include <iostream>

//using standard character input and output
using std::cout;
using std::cin;

class primegenerator // class that generates a sequence of primes
{
private:
  int last_prime_found;
  int primeNums; // number of primes found
  int currentNum;// current number being checked, if it's a prime

  //checks if inputted integer (testNum) is prime. returns a boolean.
  
public:
  // initialize primegenerator; the last prime found was 0,number of prime numbers found is 0, the current number being evaluated is 1
  primegenerator(): last_prime_found(0), primeNums(0), currentNum(1){};
  
  bool isprime(int testNum)
  {
    bool isNumPrime = true;
    if (testNum <=1) // negative numbers, 0, and 1 are not prime
      isNumPrime = false;
    for (int divisor = 2; divisor <= testNum/2; divisor ++)
      {
	if (testNum % divisor == 0)
	  {
	    isNumPrime = false; // is divisible, not prime
	    break;
	  }
      }
    return isNumPrime;
  }
  //method that counts the number of primes found
  int number_of_primes_found()
  {
    if (isprime(last_prime_found))
      primeNums ++;
    return primeNums;
  }
  //method finds the next prime, and reassigns the current prime number as the last prime number.
  //returns the found prime so it can be output
  int nextprime()
  {
    while (!(isprime(currentNum))) // composite number
      {
        currentNum ++; //check for next number
      }
    last_prime_found = currentNum;
    currentNum ++;
    return last_prime_found;
  }
};

//terminology: r or r_currentPrime is the average of two primes q and p, where q-r = r-p; (q>r>p)

int main()
{
  primegenerator primeStream1; // initialize first stream of prime numbers, such that r can be iterated over primeStream1
  int maxR = 100; // max value the original prime number (average of other 2 primes) can go up to 

  for (int r_currentPrime = 0; r_currentPrime < maxR; r_currentPrime = primeStream1.nextprime()) // use the function nextprime to get the next prime number from primeStream1
    { // another way, if wanting to specify number of outputs/primes checked
      //   for (int iterator = 0; iterator < 10; iterator++)   
      //   int r_currentPrime =  primeStream1.nextprime(); 

      primegenerator primeStream2; // use a new primeStream for restarting the iterations of prime numbers. Iterate p over primeStream2. 
      for (int p = 2; p < r_currentPrime; p = primeStream2.nextprime())
	{
	  int q = 2 * r_currentPrime - p; // define another number, q, based on r and p.
	  if (primeStream2.isprime(q)) // if/when q is prime, output the triple p,q,r where r = (p+q)/2
	    {
	      cout << r_currentPrime << " = (" << p << " + " << q << ") / 2 \n"; 
	      break; // break to stop outputting multiple triples for the same r value
	    }
	};
    };
};
