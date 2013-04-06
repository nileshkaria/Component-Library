#include <chrono>
#include <random>

namespace RNG
{

  //==========================================================================================
  class RandomNumberGenerator
  {
  public:
    //----------------------------------------------------------------------------------------
    RandomNumberGenerator();
  
    //----------------------------------------------------------------------------------------
    ~RandomNumberGenerator();

    //----------------------------------------------------------------------------------------
    int getRandomNumberInRange(int l, int u);
    
  private:
    //----------------------------------------------------------------------------------------
    std::default_random_engine _generator;
    
    //----------------------------------------------------------------------------------------
    RandomNumberGenerator(const RandomNumberGenerator&);
    RandomNumberGenerator& operator=(const RandomNumberGenerator&);
  };

} // end namespace RNG
