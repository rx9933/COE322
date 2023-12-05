/*
    Name: Arushi Sadam & Nicole Olvera
    UT EID: ars7724 & no4342
    TACC ID: rx9933 & nicoleolv
    
*/

#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
#include <algorithm>
#include <cassert>
#include <chrono>
#include <random>
#include <tuple>
#include<fstream>
#include <stdio.h>
using std::cin;
using std::cout;
using std::abs;
using std::vector;
using std::endl;
using std::swap;
using std::ofstream;
static auto rng = std::default_random_engine {}; // used to generate random input addresses (for dynamicism) and set "primeness" for such addresses

float fuelPrice = 1.0; // 1 dollar per mile, includes cost for gas + driver's wage per mile
float driverBasePrice = .5; // minimum wage for employment per distance traveled
float primeTimeCost = 2; // dollars per mile driven before prime delivery
float normalTimeCost = 1; //dollars per mile driven before regular delivery

double rand2()  // generates floats between 0 and 1
{
  std::uniform_real_distribution<double> dist(0.0, 1.0);
  return dist(rng);
}

//not used in current code:
int randomAddressCounter = 0; // number of random addresses added
float dynLength = 0; // total dynamic length

class Address {
private:
  int i, j; // coordinates
  bool primeAddress = 0;  // marks an address as prime
  bool haveSupplies = 1;

public:
  Address() : i(0), j(0) {}
  Address(int ui, int uj) : i(ui), j(uj) {}
  Address(int ui, int uj, bool prime) : i(ui), j(uj), primeAddress(prime) {}
  Address(int ui, int uj, bool prime, bool havesupplies) : i(ui), j(uj), primeAddress(prime), haveSupplies(havesupplies){}

  float manhattan_distance(const Address& other_point) const //not used, calculates manhattan distance between 2 points
  {
    return abs(i - other_point.i) + abs(j - other_point.j);
  }

  float distance(const Address& other_point) const // calculates euclidean distance
  {
    return sqrt(pow((i - other_point.i), 2) + pow((j - other_point.j), 2));
  }

  bool is_prime() const
  {
    return primeAddress;
  }

  void print() 
  {
    cout << " (" << i << ", " << j <<  "), " << "prime: " << is_prime();
  }

  bool is_depot()
  {
    return(i == 0 && j == 0); // depot is arbitrarily set to 0,0
  }

  bool supplies()
  {
    return haveSupplies; 
  }

  bool operator == (const Address &inputAdr) // used to compare to addresses
  {
    return (i == inputAdr.i && j == inputAdr.j);
  }

  friend class AddressList;  // Declare AddressList as a friend class
};
class AddressList {
protected:
  vector<Address> addresses;
  vector<Address> delivered;
  
public:
  inline static vector<Address> dyn = {}; //not used, all elements of the dynamic addresses
  AddressList() {}
  AddressList(const AddressList& from) { addresses = from.addresses; }

  float distConsequent(int i) // not used, distance between 2 consequent points
  {
    return addresses[i].Address::distance(addresses[i+1]);
  }
  void add_address(Address newAddress) 
  {
    addresses.push_back(newAddress);
  }
  bool is_valid() // not used currently, used in assert statements checking validy of code
  {
    if (addresses.size() == 0)
      return true;
    for (int num = 1; num < addresses.size() - 1; num++)
    {
      if (addresses[num].i == 0 && addresses[num].j == 0) // extra depo
      {
        return false; // not valid
      }
    }
    return (addresses[addresses.size() - 1].i == 0 && addresses[addresses.size() - 1].j == 0);
  }

  bool is_present(const Address& inputAdr) // not used, checks if address is duplicate
  {
    if (addresses.size() <= 0)
      return false;
    // ignore starting depot, but check for duplicate on last address
    std::vector<Address>::iterator it = std::find(addresses.begin() + 1, addresses.end(), inputAdr);
    return(it != addresses.end());
  }

  void remove_address(Address oldAddress) // removes first occurance of any address in addressList object
  {
    for (vector<Address>::iterator it = addresses.begin(); it != addresses.end(); ++it) 
    {
      if (it->i == oldAddress.i && it->j == oldAddress.j) 
      {
        addresses.erase(it);
        return;
      }
    }
  }

  static void printVector(std::string name, vector<Address>& inputV) // used for quick output 
  {
    cout << name << endl;
    for (Address adr : inputV)
    {
        adr.print();
    }
      cout<<endl;
  }
  
  float length() const //used as optimizing parameter, total length of addressList object
  {
    float totalLength = 0.0;
    if (addresses.size() <= 1) {
      return totalLength; // empty, no addresses
    }
    for (int i = 1; i < addresses.size(); ++i) {
      totalLength += addresses[i].distance(addresses[i - 1]); // add each consequent distance
    }
    return totalLength;
  }
  
  void print_addresses() const 
  {
    cout << "Addresses: "; 
    for (const auto& address : addresses) {
      cout << "(" << address.i << ", " << address.j << "), ";
    }
    cout << "\n"; 
  }

  int countDepots() // not used
  {
    int count = 0;
    for (Address adr : addresses)
      {
  count += adr.is_depot(); 
      }
    return count; 
  }

  Address index_closest_to(const Address& other_point) const // returns the address closest to current point, used in greedy search
  {
    float closest_distance = std::numeric_limits<float>::max(); // initialize as extremely large closest distance
    Address closest_address;
    if (addresses.size() <= 1)
    {
     return closest_address; // none, just a check
    }
    for (int i = 1; i < addresses.size() - 1; ++i) // when called on remainingAddresses (unvisited), loops through them to find the closest address
    {
        float distance = addresses[i].distance(other_point);
        if (distance < closest_distance)
        {
            closest_address = addresses[i]; // reassign closest address
            closest_distance = distance; // ...and minimum distance
        }
    }
    return closest_address;
  }

  AddressList greedy_route() const // greedy optimizing search, uses index_closest_to
  {
    AddressList route;
    if (addresses.size() < 1) 
    {
      // Handle the case where there are no addresses
      cout << "No addresses for the route.\n";
      return route;
    }
    AddressList remainingAddresses(*this);  // Make a copy of the current object
    route.add_address(addresses[0]);  // Starting from the first address 
    Address current = addresses[0];
    while (remainingAddresses.size() != 0) // Haven't finished all deliveries
    {
      Address closest_address = remainingAddresses.index_closest_to(current); // find closest address
      if (!closest_address.is_depot())
      {  // does not let extra depots get added 
        route.add_address(closest_address);
      }
      current = closest_address; //re assign current address
      remainingAddresses.remove_address(current); // remove from unvisted addresses
    }
    route.add_address(addresses[0]); // return to depot/start point
    return route;
  }

  int size() 
  {
    return (addresses.size());
  }

  void addRandomAddresses(int maxIn) 
  {
    int numAddresses = rand2() * maxIn + 1;  // a range of 1 to maxIn addresses added 
    randomAddressCounter += numAddresses;
    for (int i = 0; i < numAddresses; i++) 
    {
      int x = 0;
      int y = 0; 
      while (x == 0 && y == 0) //don't add depot as additional delivery address
      {
        x = static_cast<int>(rand2() * 10 - 5); // between +/-5
        y = static_cast<int>(rand2() * 10 - 5);
      }
      bool isPrime = (rand2()>0.8); // 20% prime, 80% regular customers
      Address newAdr = Address(x, y, isPrime, 0);
      add_address(newAdr); 
      cout << "Random Address Added: ";
      newAdr.print();
      cout<< endl;
    }
  }
  
  static void insertShuffle(vector<Address>& primes, vector<Address>& nonprimes, AddressList& path) // shuffles primes+added nonprimes and then reinserts into original vector, at a particular point
  //static because no object is created...
  {
    primes.insert(primes.end(), nonprimes.begin(), nonprimes.end()); // combines primes+nonprimes under name primes
    std::shuffle(primes.begin(), primes.end(), rng); // shuffle randomly
    path.addresses.insert(path.addresses.end(), primes.begin(), primes.end());  // insert before last depot/last element
  }
  void removeDelivered(int firstN) //for dynamic routes, updates addresses that have been delivered to
  {
    firstN+=1; 
    if (firstN > addresses.size())
      {
      firstN = addresses.size(); //max cap
      }
    auto maxSize = addresses.begin() + firstN;
    delivered.insert(delivered.end(), addresses.begin(), maxSize); // add the addresses that have delivered
    addresses.erase(addresses.begin(), maxSize); // ... and remove from existing/to-be-delivered addresses
    printVector("Delivered: ", delivered);
    dyn.insert(dyn.end(), delivered.begin(), delivered.end()); // not used
    // for (int i = 0;  i< delivered.size(); i++)
    // {
    //     AddressList::dyn.addresses.push_back(delivered[i]);
    // }
  }

  void print_delivered()
  {
    printVector("", delivered);
    cout<<endl;
  }
  
  static void insertAddress(vector<Address>& toAdd, vector<Address>& from, int start, int endN) // inserts sets of addresses at a particular location
  {
    for (int iter = start; iter < endN; iter += 1)
      {
        toAdd.insert(toAdd.end() - 1, from[iter]); // adds to the end of toAdd vector
      }
  }
};

class Route : public AddressList { // derived from AddressList class
public:
  friend class Amazon; 
  Route() 
  {
    Address depot(0, 0);
    AddressList::add_address(depot); 
    add_address(depot);
  };
  Route(AddressList adList) : AddressList(adList) {}
    void calculateDynamicCost(const Route &route)
    {
        for (int i = 0; i < route.addresses.size() - 1; ++i)
        {
            dynLength += route.addresses[i].distance(route.addresses[i + 1]);
        }
    }
  void distToDepot() // not used, the distance from last element to the depot
  {
    Address depot =Address(0,0);
    dynLength+=addresses[addresses.size()-1].distance(depot); // not used
  }
  void replace(Route &r1) // resets vector/reassigns to completely new vecotr
  {
    addresses.clear(); 
    addresses.insert(addresses.begin(), r1.addresses.begin(), r1.addresses.end());
 }

  void clear() // empties all elements in vector
  {
    addresses.clear();
  }
    
  void update(int nDelivered) // once addresses delivered
  {
    removeDelivered(nDelivered); // adds to delivered vector + removes from remainingAddresses
    if (countDepots()<2)
    {
        addresses.insert(addresses.begin(), Address(0,0)); // add depot before new deliveries, dynamic
    }
    if(!(delivered.end()-1)->is_depot()) // no depots
      addresses.insert(addresses.begin(), *(delivered.end()-1)); 
  }

  float time() // used to calculate total time/wait cost per package 
  {
    //number of prime/non-prime addresses visited
    vector<int>primes;
    vector<int>nonPrimes; 
    int totPrime = 0;
    int totNonPrime = 0;
    for (int adr = 1; adr < this->size(); adr++) // per address
      {
        bool isPrime = this->addresses[this->size() - adr - 1].is_prime(); //ignore last depot
        if (isPrime) { totPrime++; } // find total number of prime, nonprime addresses
        else { totNonPrime++; }
        primes.push_back(totPrime); // append the total number of primes already visited
        nonPrimes.push_back(totNonPrime); // total number of primes not visited
      } 
    //each step the salesman takes without attending to the primes/non-prime addresses is related to the number of primes/non-primes left
    std::reverse(primes.begin(), primes.end()); //at each index, number of prime addresses left
    std::reverse(nonPrimes.begin(), nonPrimes.end());
    float custTimeCost = 0; // total cost of delaying each package
    float step = 0.0; // distance salesman travels
    for (int adr = 1; adr < this->size() - 1; adr++) // not counting depot / return time from last address
    {
        step = this->addresses[adr - 1].distance(this->addresses[adr]); // previous step matters to future + present customers
        custTimeCost += (primes[adr] * primeTimeCost + nonPrimes[adr] * normalTimeCost) * step; // cost of each step is based on the cost each prime or nonprime delivery has to wait
    }
    return custTimeCost;
  }

  void add_address(Address newAddress) 
  {
    addresses.insert(addresses.end() - 1, newAddress);
  }
  
  static float fuelCost(float l1)
  {
    return fuelPrice * l1; // returns a price, dollars, 
  }

  static float driverCost(float l1)
  {
    float cost = 0.0;
    if (l1 > 1e-6) //moved somewhat
      cost += driverBasePrice;// returns a price, dollars, 
    return cost;
  }

  static float timeCost(Route newPath1)
  {
    return newPath1.time(); // returns a price, dollars, 
  }

  static float totalCost(Route newPath1)
  {
    float l1 = newPath1.length();
    return fuelCost(l1) + driverCost(l1) + timeCost(newPath1); // sums up all net costs
  }

  bool fullySupplied() // have supplies before delivery?
  {
    std::vector<Address>::const_iterator depotIndex = std::find(addresses.begin() + 1, addresses.end(), Address(0,0));
    for (auto i = addresses.begin()+1; i < depotIndex; i++)
    {
        if (!i->supplies()) {return false; } // does not have package
    }
    return true; 
  }

  Route opt2(bool dynamic = false) 
    {
    if (addresses.size() - 1 == 0)  // if the depot is the only address
        {
        return *this;
        }
    float minCost = std::numeric_limits<float>::max();  // ensures anything will be smaller than the current value 
    Route optimizedPath = Route(*this);  
    bool isBeingOptimized = true;
    while (isBeingOptimized)  // tries different combinations until a better one is found  
        {
        isBeingOptimized = false;  
        for (int m = 1; m < addresses.size() - 2; m++)  // loops through all possible combinations 
            {
        for (int n = m + 1; n < addresses.size() - 1; n++) 
                {
            Route newAddressOrder = optimizedPath.reverse_route(m, n);  // and reverses them 
            float newCost = totalCost(newAddressOrder);  // calculates the total cost of this new order of addresses 
            bool change = newCost < minCost;  // change is true if this new order costs less than the previous calculated one 
            if (dynamic) {
            change = change && newAddressOrder.fullySupplied();  //  checks if this new order of addresses is fully supplied (driver has all the packages)  
            // depot should be before all new/added addresses
                    }
            if (change) // if we did find an improvement, then update all other values with this address order
                    {
            optimizedPath = newAddressOrder;
            minCost = newCost;
            isBeingOptimized = true;
            break;
                    }
                }
        if (isBeingOptimized) { break;  }
        
            }
        }
        return optimizedPath;
    }

  Route reverse_route(int m, int n) const 
    {  // takes two indices as input 
        if (m >= n || n >= addresses.size())   
            {
            // Invalid indices, return a copy of the current list
            return *this;
            }  
        Route reversedList(*this);  // creates a copy of the route 
        auto it_begin = reversedList.addresses.begin() + m;  // iterator pointing to the starting position of the range we want to reverse   
        auto it_end = reversedList.addresses.begin() + n + 1;  // iterator pointing to one position past the last element of the range we want to reverse 
        reverse(it_begin, it_end);  // uses the reverse algorithm to reverse the order of addresses between m and n 
        return reversedList;
    }

  std::tuple<vector<Address>, vector<Address> > getPrimesAndNonPrimes(const Route& path, int start, int end) 
  {       
  vector<Address>primes,nonPrimes;
  for (int i = start; i < end; i++)  // puts all prime addresses in a primes vector 
    {
      if (path.addresses[i].is_prime()) 
	{
	  primes.push_back(path.addresses[i]);
	}
      else
	{
	  nonPrimes.push_back(path.addresses[i]);  // puts all non primes in a vector 
	}
    }
  return std::make_tuple(primes, nonPrimes);  // vector that contains both primes and nonprimes together 
}

  // Function that removes consecutive depots--a check, in case extra depots are added
  void removeExtraDepots()// not used
  {
    for (auto it = addresses.begin() + 1; it != addresses.end() - 1;){
      if (it->is_depot() && (it - 1)->is_depot())
      {
         it = addresses.erase(it);
      } 
      else
      {
        it++;
      }
    }
  }
};

class Amazon: Route{
public:
  static float totalCost(Route newPath1, Route newPath2) //get total cost of 2 salesmen
  {
    return Route::totalCost(newPath1) + Route::totalCost(newPath2);
  }
    
  std::tuple<Route, Route> combineSegments(Route & path1, int m1, int n1, Route & path2, int m2, int n2) // keeps primes in original vectors and swaps non primes from each subvector
  {
    Route newPath1,newPath2; // complete empty new routes
    newPath1.clear();
    newPath2.clear();
    // 1: start to m remains same, 2: m-n becomes random shuffle of original primes + secondary vecotor's non primes, 3: n-end stays the same
    //inital portions remain the same
    //1:
    newPath1.addresses.insert(newPath1.addresses.begin(), path1.addresses.begin(), path1.addresses.begin()+m1);
    newPath2.addresses.insert(newPath2.addresses.begin(), path2.addresses.begin(), path2.addresses.begin()+m2);

    //2:
    //seperate into primes + nonprimes for each path
    auto [primes1, nonPrimes1] = getPrimesAndNonPrimes(path1, m1, n1);
    auto [primes2, nonPrimes2] = getPrimesAndNonPrimes(path2, m2, n2);

    //shuffle primes from original vector + non primes from other vector + insert all into newPaths (after start to m)
    insertShuffle(primes1, nonPrimes2, newPath1);
    insertShuffle(primes2, nonPrimes1, newPath2);

    //3:
    //last portion remains the same
    newPath1.addresses.insert(newPath1.addresses.end(), path1.addresses.begin()+n1, path1.addresses.end()); 
    newPath2.addresses.insert(newPath2.addresses.end(), path2.addresses.begin()+n2, path2.addresses.end());  
    
    return std::make_tuple(newPath1, newPath2); // return new routes
  }

  std::tuple<Route, Route> multiPaths(Route path1, Route path2, bool dynamic = false, bool greedy = false, bool opt = true) 
  {
    float minCost = std::numeric_limits<float>::max(); // maximize at initialization

    Route optimizedPath1(path1), optimizedPath2(path2);
    bool isBeingOptimized = true, restart = false;
    int count = 0;

    while (isBeingOptimized || count < 5) // continue to look for an improvement until none is found or after a maximum count is reached 
    {
      count++;
      restart = false;
      isBeingOptimized = false;
      // loops to select segments in both paths 
      for (int m1 = 1; m1 <= optimizedPath1.addresses.size() - 1 && !restart; m1++)
      {
        for (int n1 = m1; n1 <= optimizedPath1.addresses.size() - 1 && !restart; n1++)
        {
          for (int m2 = 1; m2 <= optimizedPath2.addresses.size() - 1 && !restart; m2++)
          {
            for (int n2 = m2; n2 <= optimizedPath2.addresses.size() - 1 && !restart; n2++)
            {
              //extra 0 - 0 swap, to allow for 0 - >0 swaps (0  - many swaps)
              // may be reversed or not
              for (int randomS = 0; randomS < 10 && !restart; randomS++) // extra iterations for more optimized route. ...
              {
              // using structured binding 
                auto [newPath1, newPath2] = combineSegments(optimizedPath1, m1, n1, optimizedPath2, m2, n2);
                // apply optimization technique specified in main 
                if (greedy)
                {
                    newPath1.greedy_route();
                    newPath1.greedy_route();
                }
                if (opt)
                {
                    newPath1.opt2(dynamic);
                    newPath2.opt2(dynamic);
                }

                 //calculates the new cost of the combined paths
                float newCost = totalCost(newPath1, newPath2);
                bool change = newCost < minCost;  // checks for improvement 
                if (dynamic)  // and applies to check for packages 
                {
                    change = change && newPath1.fullySupplied() && newPath2.fullySupplied();
                    // depot before all new/added addresses
                }
                if (change)  // if an improvement is found, then calculate update our variables that show improvement
                {
                  restart = true;
                  isBeingOptimized = true;
                  optimizedPath1 = newPath1;
                  optimizedPath2 = newPath2;
                  minCost = newCost;
                  cout << "min cost  " << minCost<<endl;
                  count = 0;
                }
              }
            }
          }
        }
      }
      if (dynamic) //checks for packages once we found the most optimized route 
      {
        if (!(optimizedPath1.fullySupplied() && optimizedPath2.fullySupplied()))
        {
          isBeingOptimized = true; // continue checking for optimial solution, conditions not satisfied
        }
      }
    }      
    return std::make_tuple(optimizedPath1, optimizedPath2);
  }
};



int main(){

 // auto start_time = std::chrono::high_resolution_clock::now();
  Route deliveries;
  Route deliveries2;

//   deliveries.add_address(Address(16, 2));
//   deliveries.add_address(Address(-2, 20));
//   deliveries.add_address(Address(3, 10));
//   deliveries.add_address(Address(3, 10));
//   deliveries.add_address(Address(-8, -8,1));
//   deliveries.add_address(Address(16, 4));
//   deliveries.add_address(Address(0,-8));
//   deliveries.add_address(Address(0, 10,1));
//   deliveries.add_address(Address(-33, 17));

  deliveries.add_address(Address(22, 31));
  deliveries.add_address(Address(3, 3));
  deliveries.add_address(Address(3,-2));

  deliveries2.add_address(Address(0,-4)); 
  deliveries2.add_address(Address(-10,0));
  deliveries2.add_address(Address(0, -2));
  deliveries2.add_address(Address(-4, -4));
  deliveries2.add_address(Address(3, 1));
  deliveries2.add_address(Address(3, 3));
  deliveries2.add_address(Address(3, 0));
  deliveries.add_address(Address(4, 0));
  deliveries.add_address(Address(-4,-4));
//   deliveries2.add_address(Address(-2, -8));
//   deliveries2.add_address(Address(3, -9, 1));
//   deliveries2.add_address(Address(1, 22));
//   deliveries2.add_address(Address(-10, 3));
//   deliveries2.add_address(Address(7, 3, 1));

// for (int i =0; i <10; i++)
// {
//     deliveries.add_address(Address(i, i+1));
//     deliveries2.add_address(Address(i, i+1));
// }

  // ONE SALESMAN
///*
  cout << "ONE SALESMAN" << endl << endl;
  cout << "Initial Route:\n";
  deliveries.print_addresses();
  cout << "Route Length: " << deliveries.length() << "\n";
  cout<< "Route Cost: " << Route::totalCost(deliveries)<<endl;
  cout<<endl;
//*/
///*
  Route greedy_route = deliveries.greedy_route();
  cout << "Greedy Route:\n"; 
  greedy_route.print_addresses();
  cout << "Route Length: " << greedy_route.length() << "\n";
  cout << "Route Cost: " << Route::totalCost(greedy_route) << "\n";
  cout<<endl;

  cout << "Opt2 Route \n";
  Route opt2Route = deliveries.opt2();
  opt2Route.print_addresses();
  cout << "Route Length: " << opt2Route.length() << "\n";
  cout << "Route Cost: " << Route::totalCost(opt2Route) << "\n\n";
//*/
  /////*********TIME CHECKS *********////////
  /*
  auto start_time = std::chrono::high_resolution_clock::now();
  Route route = deliveries.opt2();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
  cout << "Addresses List Size" << deliveries.size() << endl << 
  "Opt2 Route Runtime: " << duration.count() << " microseconds\n";
  */
  //***RESULTS*/
  /*
    SIZE: 10     RUNTIME: 28 microseconds        ROUTE LENGTH: 21.5296
    SIZE: 100    RUNTIME: 27935 microseconds     ROUTE LENGTH: 276.066
    SIZE: 500    RUNTIME: 3350971 microseconds   ROUTE LENGTH: 1407.43
    SIZE: 1000   RUNTIME: 26411114 microseconds  ROUTE LENGTH: 2821.63
  */
 ///*
  cout << "Greedy-Opt2 Route \n";
  Route greedyOpt2Route = greedy_route.opt2(); 
  greedyOpt2Route.print_addresses();
  cout << "Route Length: " << greedyOpt2Route.length() << "\n";
  cout << "Route Cost: " << Route::totalCost(greedyOpt2Route) << "\n\n";
//  */

  cout << "TWO SALESMEN" << endl;

  // TWO SALESMEN
  Route path1 = deliveries;
  Route path2 = deliveries2;

  cout << "Initial Route 1:\n";
  path1.print_addresses();
  cout << "Initial Route 2:\n";
  path2.print_addresses();

  //GREEDY ROUTE

  Amazon amazon;  // created an instance of Amazon 
 // /*
  auto multiPathGreed = amazon.multiPaths(path1, path2, false,true,false); //dynamic, greedy, opt2
  Route greedRoute1 = std::get<0>(multiPathGreed);
  Route greedRoute2  = std::get<1>(multiPathGreed);
  cout << "Greedy Route 1:\n";
  greedRoute1.print_addresses();
  cout << "Optimized Combined Route Length: " << greedRoute1.length() << endl;
  cout << "Route Cost: " << Route::totalCost(greedRoute1) << endl;
  cout << endl;
  cout << "Greedy Route 2:\n";
  greedRoute2.print_addresses();
  cout << "Optimized Combined Route Length: " << greedRoute2.length() << endl;
  cout << "Route Cost: " << Route::totalCost(greedRoute2) << endl;
  cout << endl;
//*/

  //OPT2 ROUTE
  auto multiPathOpt2 = amazon.multiPaths(path1, path2, false,false,true); //dynamic, greedy, opt2
  Route opt2Route1 = std::get<0>(multiPathOpt2);
  Route opt2Route2  = std::get<1>(multiPathOpt2);
  cout << "Opt2 Route 1:\n";
  opt2Route1.print_addresses();
  cout << "Optimized Combined Route Length: " << opt2Route1.length() << endl;
  cout << "Route Cost: " << Route::totalCost(opt2Route1) << endl;
  cout << endl;
  cout << "Opt2 Route 2:\n";
  opt2Route2.print_addresses();
  cout << "Optimized Combined Route Length: " << opt2Route2.length() << endl;
  cout << "Route Cost: " << Route::totalCost(opt2Route2) << endl;
  cout << endl;

///*
  //GREEDY OPT2 ROUTE  
  auto multiPathGreedOpt = amazon.multiPaths(path1, path2, false,true,true); //second true is for bool greedy_opt2
  Route greedyOpt2Route1 = std::get<0>(multiPathGreedOpt);
  Route greedyOpt2Route2  = std::get<1>(multiPathGreedOpt);
  //*/
///*
  cout << endl;
  cout << "Greedy-opt2 Final Route 1:\n";
  greedyOpt2Route1.print_addresses();
  cout << "Greedy-opt2 Route Length 1: " << greedyOpt2Route1.length() << endl;
  cout << "Greedy-opt2 Route Cost 1: " << Route::totalCost(greedyOpt2Route1) << endl << endl;
  cout << "Greedy-opt2 Final Route 2:\n";
  greedyOpt2Route2.print_addresses();
  cout << "Greedy-opt2 Route Length 2: " << greedyOpt2Route2.length() << endl;
  cout << "Greedy-opt2 Route Cost 2: " << Route::totalCost(greedyOpt2Route2) << endl;
//   auto end_time = std::chrono::high_resolution_clock::now();
//   auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
//     cout << "Addresses List Size" << deliveries.size() << endl << 
//   "Opt2 Route Runtime: " << duration.count() << " microseconds\n";
//*/

///*
 //Dynamicism with opt2; make sure to have at least 1 address already in each route (initialize)
  cout << "\nRANDOM ADDRESSES ADDED\n";
  cout << "\nReturn to Depot Before New Deliveries Strategy:\n";
  cout << "\nInitial Paths:\n";
  deliveries.print_addresses();
  deliveries2.print_addresses();
  int adrPerDay = 3; // number of addresses delivered per day
  int maxIn = 1;     // max number of input addresses per day
  int count = 0;
  randomAddressCounter += deliveries.size() + deliveries2.size()-4; // 4 depots

  while ((opt2Route1.size() > 2 || opt2Route2.size() > 2) && count < 10) // one address is the current location (already deliveried) and the other is the depot at the end
  { 
    opt2Route1.addRandomAddresses(maxIn);
    opt2Route2.addRandomAddresses(maxIn);
    cout << "\nPlanned Addresses:\n";
    opt2Route1.print_addresses();
    opt2Route2.print_addresses();
    auto newOptimizedPaths = amazon.multiPaths(opt2Route1, opt2Route2, true); // default is to use plain opt2 
    opt2Route1 = std::get<0>(newOptimizedPaths);
    opt2Route2 = std::get<1>(newOptimizedPaths);
    cout << "\nOptimized Addresses:\n";
    opt2Route1.print_addresses();
    opt2Route2.print_addresses();

    opt2Route1.calculateDynamicCost(opt2Route1);
    opt2Route2.calculateDynamicCost(opt2Route2);

    opt2Route1.update(adrPerDay);
    opt2Route2.update(adrPerDay);
    count++;
  }
    // opt2Route1.distToDepot();
    // opt2Route1.distToDepot();

  cout << "\nFinal Delivered Address for Driver 1:";
  Address(0,0).print(); // returned to depot
  cout << "\nFinal Delivered Address for Driver 2:"<<endl; 
  Address(0,0).print(); // returned to depot
//   cout << endl<< "number of tot addresses" << randomAddressCounter<<endl;
//   AddressList::printVector("dyn vector", AddressList::dyn); // all visited addresses
//   cout << "Total distance" << dynLength<<endl;
//  */
///*
  //Redirect standard output to the file
  freopen("singleSalesmanOutput.txt", "w", stdout);

  printf("Initial Route:\n");
  deliveries.print_addresses();

  printf("Greedy Route:\n");
  greedy_route.print_addresses();

  printf("Only Opt2 Route:\n");
  opt2Route.print_addresses();

  printf("Greedy-Opt2 Route:\n");
  greedyOpt2Route.print_addresses();

  fclose(stdout);


  freopen("multipleSalesmanOutput.txt", "w", stdout);

  printf("1 Initial Route:\n");
  path1.print_addresses();
   printf("2 Initial Route:\n");
  path2.print_addresses();
 
  printf("1 Greedy Route:\n");
  greedRoute1.print_addresses();
  printf("2 Greedy Route:\n");
  greedRoute2.print_addresses();

  printf("1 Opt2 Route:\n");
  opt2Route1.print_addresses();
  printf("2 Opt2 Route:\n");
  opt2Route2.print_addresses();

  printf("1 Greedy-Opt2 Route:\n");
  greedyOpt2Route1.print_addresses();
  printf("2 Greedy-Opt2 Route:\n");
  greedyOpt2Route2.print_addresses();
  
  fclose(stdout);
//*/
// auto end_time = std::chrono::high_resolution_clock::now();
// auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
  
//  cout << "Addresses List Size" << deliveries.size() << endl << 
//   "Route Runtime: " << duration.count() << " microseconds\n";
}