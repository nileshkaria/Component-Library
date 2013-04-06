#include <iostream>
#include <vector>

#include "random_number_generator.h"

using namespace std;
using namespace RNG;

/*
int bigrand()
{
  return abs(RAND_MAX*rand() + rand());
}

int randint(int l, int u)
{
  return l + bigrand() % (u - l + 1);
}
*/

namespace RandomizedPartitionQuicksort
{
  //----------------------------------------------------------------------------------------
  void quicksort(vector<int> & x, int l, int u)
  {
    if(l >= u)
      return;

    RandomNumberGenerator rng;
    
    int random = rng.getRandomNumberInRange(l, u);
    swap(x[l], x[random]);

    int t = x[l];
    int i = l;
    int j = u + 1;

    while(true)
    {
      do
      {
	++i;
      }while(i <= u && x[i] <= t);
    
      do
      {
	--j;
      }while(x[j] > t);
      
      if(i > j)
	break;
    

      swap(x[i], x[j]);
    }
    
    //Get back randomly picked pivot in its place
    swap(x[l], x[j]);

    quicksort(x, l, j - 1);
    quicksort(x, j + 1, u);  
  }

} // end namespace RandomizedPartitionQuicksort

int main()
{
  vector<int> x;

  x.reserve(10);

  cout << "Unsorted vector" << endl;
  for(int i = 20; i > 0; --i)
  {
    cout << i << " ";

    x.push_back(i);
  }
  cout << endl;

  RandomizedPartitionQuicksort::quicksort(x, 0, x.size() - 1);

  cout << "Sorted vector" << endl;
  for(int i = 0; i < x.size(); ++i)
    cout << x[i] << " ";

  cout << endl;
  cout << "-------------------" << endl;

  cout << "Quicksort on sorted vector" << endl;

  RandomizedPartitionQuicksort::quicksort(x, 0, x.size() - 1);

  cout << "Sorted vector" << endl;
  for(int i = 0; i < x.size(); ++i)
    cout << x[i] << " ";

  cout << endl;
  cout << "-------------------" << endl;

  cout << "Quicksort on vector with dupes" << endl;

  for(int i = 10; i > 0; --i)
  {
    cout << i << " ";

    x.push_back(i);
  }
  cout << endl;

  RandomizedPartitionQuicksort::quicksort(x, 0, x.size() - 1);

  cout << "Sorted vector" << endl;
  for(int i = 0; i < x.size(); ++i)
    cout << x[i] << " ";

  cout << endl;
  cout << "-------------------" << endl;

  cout << "Quicksort on sorted vector" << endl;

  RandomizedPartitionQuicksort::quicksort(x, 0, x.size() - 1);

  cout << "Sorted vector" << endl;
  for(int i = 0; i < x.size(); ++i)
    cout << x[i] << " ";

  cout << endl;
  cout << "-------------------" << endl;

  return 0;
}
