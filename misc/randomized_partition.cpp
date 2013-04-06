#include <cstdlib>
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

namespace RandomizedPartition
{
  //----------------------------------------------------------------------------------------
  void partition(vector<int> & x, int l, int u, int r)
  {
    if(r > x.size() || r <= 0)
    {
      cout << "Rank " << r << " not within bounds." << endl;
      return;
    }
    
    if(l >= u)
    {
      if(r - 1 == l)
	cout << "Element " << x[l] << " is the " << r << " ranked element." << endl;
      else if(r - 1 == u)
	cout << "Element " << x[u] << " is the " << r << " ranked element." << endl;      
      
      return;
    }

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
      }while(i <= u && x[i] < t);
	
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

    //cout << "r= " << r << " j= " << j << " x[" << j << "]= " << x[j] << endl;  

    if(r - 1 == j)
    {
      cout << "Element " << x[j] << " is the " << r << " ranked element." << endl;
      return;
    }
    //Partition left
    else if(r - 1 < j)
    {
      partition(x, l, j - 1, r);
    }
    //Partition right
    else 
      partition(x, j + 1, u, r);  
  }

} // end namepace RandomizedPartition

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

  RandomizedPartition::partition(x, 0, x.size() - 1, 47);
  RandomizedPartition::partition(x, 0, x.size() - 1, 7);
  RandomizedPartition::partition(x, 0, x.size() - 1, 0);

  return 0;
}
