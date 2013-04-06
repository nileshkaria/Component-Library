#include <iostream>
#include <vector>
#include <bitset>
#include <cmath>
#include <algorithm>

using namespace std;

namespace Combinatronics
{
  //==========================================================================================
  template<typename T>
  class Combinatronics
  {
  public:
    //----------------------------------------------------------------------------------------
    Combinatronics();

    //----------------------------------------------------------------------------------------
    ~Combinatronics();
    
    //----------------------------------------------------------------------------------------
    void permutations(int n, vector<vector<T> > &perms);
    void permutations(vector<T> &v, vector<vector<T> > &perms);
    
    //----------------------------------------------------------------------------------------
    void all_permutations(int n, vector<vector<T> > &perms);
    void all_permutations(vector<vector<T> > & combs, vector<vector<T> > &perms);

    //----------------------------------------------------------------------------------------
    void combinations(int numBits, vector<vector<T> > &combs);
    void combinations(vector<vector<T> > &combs);

    //----------------------------------------------------------------------------------------
    void print(const vector<T> &v);
    void print(const vector<vector<T> > &v);

  private:
    //----------------------------------------------------------------------------------------
    Combinatronics(const Combinatronics&);
    Combinatronics & operator=(const Combinatronics&);

    //----------------------------------------------------------------------------------------
    static const int NumBits         = 3;
    static const int NumCombinations = 8; //2^NumBits
  };

  //------------------------------------------------------------------------------------------
  template<typename T>
  const int Combinatronics<T>::NumBits;

  //------------------------------------------------------------------------------------------
  template<typename T>
  const int Combinatronics<T>::NumCombinations;

  //------------------------------------------------------------------------------------------
  template<typename T>
  Combinatronics<T>::Combinatronics() {}

  //------------------------------------------------------------------------------------------
  template<typename T>
  Combinatronics<T>::~Combinatronics() {}

  //------------------------------------------------------------------------------------------
  template<typename T>
  void Combinatronics<T>::print(const vector<T> &v)
  {
    cout << "--------------------------" << endl;
    for(size_t i = 0; i < v.size(); ++i)
      cout << v[i] << " ";
    cout << "--------------------------" << endl;
  }

  //------------------------------------------------------------------------------------------
  template<typename T>
  void Combinatronics<T>::print(const vector<vector<T> > &v)
  {
    cout << "--------------------------" << endl;
    for(size_t i = 0; i < v.size(); ++i)
    {
      for(size_t j = 0; j < v[i].size(); ++j)
      {
	cout << v[i][j] << " ";
      }  
      cout << endl;
    }
    cout << "--------------------------" << endl;
  }

  //------------------------------------------------------------------------------------------
  template<typename T>
  void Combinatronics<T>::combinations(vector<vector<T> > &combs)
  {
    //Set NumBits and NumCombinations
    for(int i = 0; i < NumCombinations; ++i)
    {
      bitset<NumBits> b(i);
      vector<T> c;
      for(size_t j = 0; j < b.size(); ++j)
      {
	if(b[j])
	  c.push_back(j);	  
      }
      
      combs.push_back(c);
    }
  }

  //------------------------------------------------------------------------------------------
  template<typename T>
  void Combinatronics<T>::combinations(int numBits, vector<vector<T> > &combs)
  {
    //Set NumBits and NumCombinations
    for(int i = 0; i < pow(2.0, static_cast<double>(numBits)); ++i)
    {
      vector<T> c;
      for(size_t j = 0; j < numBits; ++j)
      {
	if(i & (0x1 << j))
	  c.push_back(j);	  
      }
      
      combs.push_back(c);
    }
  }

  //------------------------------------------------------------------------------------------
  template<typename T>
  void Combinatronics<T>::permutations(int n, vector<vector<T> > &perms)
  {
    vector<T> v;
    for(size_t i = 0; i < n; ++i)
      v.push_back(i);
    
    permutations(v, perms);
  }

  //------------------------------------------------------------------------------------------
  template<typename T>
  void Combinatronics<T>::permutations(vector<T> &v, vector<vector<T> > &perms)
  {
    if(!v.size())
      return;
    
    sort(v.begin(), v.end());
    reverse(v.begin(), v.end());
    do
    {
      perms.push_back(v);
    }while(prev_permutation(v.begin(), v.end()));
  }

  //------------------------------------------------------------------------------------------
  template<typename T>
  void Combinatronics<T>::all_permutations(vector<vector<T> > & combs, vector<vector<T> > &perms)
  {
    for(size_t i = 0; i < combs.size(); ++i)
      permutations(combs[i], perms);
  }

  //------------------------------------------------------------------------------------------
  template<typename T>
  void Combinatronics<T>::all_permutations(int n, vector<vector<T> > &perms)
  {
    vector<vector<T> > combs;
    combinations(n, combs);
    
    all_permutations(combs, perms);
  }

} // end namepace Combinatronics


int main()
{
  Combinatronics::Combinatronics<int> c;

  cout << "Combinations " << endl;
  vector<vector<int> > combs;
  c.combinations(combs);
  c.print(combs);

  combs.clear();

  cout << "Combinations " << endl;  
  c.combinations(3, combs);
  c.print(combs);

  cout << "Permutations (given number)" << endl;
  vector<vector<int> > perms;
  c.permutations(3, perms);
  c.print(perms);

  perms.clear();

  cout << "Permutations (given combinations)" << endl;
  vector<int> v;
  for(size_t i = 0; i < 3; ++i)
    v.push_back(i);

  c.permutations(v, perms);
  c.print(perms);

  perms.clear();

  cout << "All Permutations (given combinations)" << endl;
  c.all_permutations(combs, perms);
  c.print(perms);

  perms.clear();
  combs.clear();

  cout << "All Permutations (given number)" << endl;
  c.all_permutations(3, perms);
  c.print(perms);

  perms.clear();

  return 0;
}
