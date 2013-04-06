// uniform_int_distribution::operator()
#include <iostream>
#include <bitset>
#include <chrono>
#include <random>
#include <set>

using namespace std;

class Password
{
private:
  Password(const Password &);
  Password & operator=(const Password &);

  /*
  bitset<64>                _msb;
  bitset<64>                _lsb;
  */

  unsigned long             _msb;
  unsigned long             _lsb;

  //vector<pair<char, int> >  _sequence;

public:
  
  Password() :
    _msb(0UL), //(18446744073709551615UL),
    _lsb(0UL) //(18446744073709551615UL),
    //_sequence()
  {}

  ~Password()
  {}

  void generateSequence()
  {
    // construct a trivial random generator engine from a time-based seed:
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    
    //Get letter between 'a' and 'l'
    uniform_int_distribution<int> dot(97, 108);

    //Get color between 0 and 3
    uniform_int_distribution<int> color(0, 3);
    
    set<int> seen;

    size_t count(0);

    //Twelve point grid with each point having one of four colors.
    //For test purposes we mandate selection of 8 unique points with random colors.
    //The unselected four pointes remaining are later added sequentially.  

    // (8 + 2) x 8 = 80 bits
    while(seen.size() < 8)
      {
	int num(dot(generator));

	if(seen.find(num) == seen.end())
	  {
	    seen.insert(num);

	    int c(color(generator));

	    //_sequence.push_back(make_pair(static_cast<char>(num), c));

	    if(count == 0)
	      {
		_lsb |= c;
	      }
	    else if(count < 60)
	      {
		_lsb <<= 2;
		_lsb |= c;
	      }
	    else
	      {
		_msb <<= 2;
		_msb |= c;
	      }

	    count += 2;

	    if(count < 60)
	      {
		_lsb <<= 8;
		_lsb |= num;
	      }
	    else
	      {
		_msb <<= 8;
		_msb |= num;
	      }

	    count += 8;

	    //cout << static_cast<char>(num) << " " << c << " ";
	  }
      }

    // (8 + 2) x 4 = 40 bits   
    for(size_t num = 97; num <= 108; ++num)
      {
	if(seen.find(num) == seen.end())
	  {
	    seen.insert(num);

	    _msb <<= 10;
	    _msb |= num;

	    count += 10;

	    //_sequence.push_back(make_pair(static_cast<char>(num), 0));

	    //cout << static_cast<char>(num) << " " << 0 << " ";
	  }
      }
    
    //Generate 8 random bits (maybe from the unique userid ie. email address)
    uniform_int_distribution<int> userid(0, 127);    

    int id(userid(generator));

    _lsb <<= 4;
    _lsb |= (id & 0x00aa);

    _msb <<=4;
    _msb |= (id & 0xaa00);

    cout << _msb << _lsb << endl;
  }

};

int main()
{
  //cout << "Int : " << b.to_ulong() << endl;
  //NOTE -  99952029 unique out of 100000000

  Password p;

  p.generateSequence();

  return 0;
}
