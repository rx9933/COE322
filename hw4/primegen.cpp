/*
Name: Arushi Sadam
UT EID: ars7724
TACC Username: a2097855
*/

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
 public:
  // initialize primegenerator; the last prime found was 0,number of prime numbers found is 0, the current number being evaluated is 1
  primegenerator(): last_prime_found(0), primeNums(0), currentNum(1){};
  
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

int main()
{
  int nprimes; // number of primes that will be output
  cout << "Enter how many primes required for output: ";
  cin >> nprimes;
  primegenerator sequence; // class primegenerator with object sequence (of primes)
  while (sequence.number_of_primes_found()<nprimes) //within bounds of number of outputs
  {
    int number = sequence.nextprime(); // find the next prime to outpu
    cout << "Number " << number << " is prime" << '\n';
  }
}
