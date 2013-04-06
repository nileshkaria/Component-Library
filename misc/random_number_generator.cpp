#include "random_number_generator.h"

using namespace RNG;
using namespace std;

namespace RNG
{
  // construct a trivial random generator engine from a time-based seed:
  //----------------------------------------------------------------------------------------
  RandomNumberGenerator::RandomNumberGenerator() :
    _generator(chrono::system_clock::now().time_since_epoch().count())
  {}
  
  //----------------------------------------------------------------------------------------
  RandomNumberGenerator::~RandomNumberGenerator()
  {}
  
  //----------------------------------------------------------------------------------------
  int RandomNumberGenerator::getRandomNumberInRange(int l, int u)
  {
    uniform_int_distribution<int> uid(l, u);

    return uid(_generator);
  }

} // end namespace RNG

//Test
/*
#include<iostream>

int main()
{
  RandomNumberGenerator rng;

  for(size_t i = 0; i < 100; ++i)
    cout << "RandomNumber " << rng.getRandomNumberInRange(0, 100) << endl;

  return 0;
}
*/
