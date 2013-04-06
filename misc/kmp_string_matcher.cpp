#include <iostream>

#include "kmp_string_matcher.h"

using namespace std;

//Knuth Morris Pratt algorithm to find substring matches.
//Given a pattern of characters P[1..q] match text characters T[s+1..s+q], 
//what is the least shift s' > s such that 
// P[1..k] == T[s'+1..s'+k] where (s' + k) == (s + q)

//Running time :
//Precompute function = (theta) O(m) 
//Finding matches     = (theta) O(n)

namespace KMP
{

  //----------------------------------------------------------------------------------------
  KMPStringMatcher::KMPStringMatcher() 
  {}

  //----------------------------------------------------------------------------------------
  KMPStringMatcher::~KMPStringMatcher()
  {}

  //Precomputation required: 
  //The prefix function encapsulates the knowledge of how the pattern matches against itself.
  //Given a pattern P[1..m], the prefix function for
  // the pattern P is the function PI[1..m] -> {0,1,..,m-1} such that
  //PI[q] is the length of the longest prefix of P that is a proper suffix of the prefix Pq.
  //----------------------------------------------------------------------------------------
  void KMPStringMatcher::computePrefixFunction(const string &p, 
					       vector<int>  &PI)
  {
    PI.resize(p.size());
    
    PI[0] = 0;
    
    //Number of characters matched
    int k = 0;
    
    for(int q = 2; q <= p.size(); ++q)
    {
      //Next character does not match
      while(k > 0 && p.at(k) != p.at(q - 1))
	k = PI[k - 1];
      
      //Next character matches
      if(p.at(k) == p.at(q - 1))
	++k;

      //Characters in prefix of size (q - 1) 
      //with matching suffix of maximum size k 
      PI[q - 1] = k;
    }
    
    //Print prefix function
    cout << "Prefix function: " << endl;
    for(size_t i = 0; i < p.size(); ++i)
      cout << p.at(i) << " ";

    cout << endl;
    
    for(size_t i = 0; i < PI.size(); ++i)
      cout << PI[i] << " ";
    
    cout << endl;
  }

  //----------------------------------------------------------------------------------------
  void KMPStringMatcher::findMatches(const string& t,
				     const string& p,
				     vector<int> & rShift)
  {
    cout << "Text string : " << t << endl;
    cout << "Pattern string: " << p << endl;
    
    vector<int> PI;
    computePrefixFunction(p, PI); 

    //Number of characters matched
    int q = 0;
    
    //Scan text from left to right
    for(int i = 1; i <= t.size(); ++i)
    {
      //Next character does not match
      while(q > 0 && p.at(q) != t.at(i - 1))
	q = PI[q - 1];
      
      //Next character matches
      if(p.at(q) == t.at(i - 1))
	++q;
      
      //Is all of p matched?
      if(q == p.size())
      {
	//Record the shift at which the pattern matches
	rShift.push_back(i - p.size());
	
	q = PI[q - 1];
      }
    }
  }

} // end namespace KMP

int main()
{
  string t("bacbababacbab");
  string p("bab");

  vector<int> shift;

  KMP::KMPStringMatcher::findMatches(t, p, shift);

  for(size_t i = 0; i < shift.size(); ++i)
    cout << "Pattern " << p << " occurs with shift " << shift[i] << endl;
 
  return 0;
}
