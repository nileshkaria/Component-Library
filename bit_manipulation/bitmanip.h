#ifndef __BIT_MANIP_H_GUARD_
#define __BIT_MANIP_H_GUARD_

#include <cmath>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <sstream>

/*

Set union
    A | B
Set intersection
    A & B
Set subtraction
    A & ~B
Set negation
    ALL_BITS ^ A
Set bit
    A |= 1 << bit
Clear bit
    A &= ~(1 << bit)
Test bit
    (A & 1 << bit) != 0 
Test last bit
    (A & 1) != 0
Power of 2
    A & (A-1) == 0

NOTE : &, | have lesser precedence than == and !=
*/

namespace BitManip
{
  //==========================================================================================
  //Preprocess bitcount table for ints between 0-255
  //Template metaprogramming class based on example here:
  //http://stackoverflow.com/questions/2226291/is-it-possible-to-create-and-initialize-an-array-of-values-using-template-metapr
  //------------------------------------------------------------------------------------------
  //------------------------------------------------------------------------------------------
  template <unsigned int n>
    struct bitcount_table 
    {
      bitcount_table<n - 1> bt;
      unsigned int x;

      //--------------------------------------------------------------------------------------    
    bitcount_table() : 
      x(__builtin_popcount(n - 1)) 
      {}

      //--------------------------------------------------------------------------------------    
      unsigned int operator[](unsigned int i)
      {
	return reinterpret_cast<int*>(&bt)[i];
      }

      //--------------------------------------------------------------------------------------    
      const unsigned int operator[](unsigned int i) const
      {
	return reinterpret_cast<int*>(&bt)[i];
      }
    };

  template <>
    struct bitcount_table<1> 
    {
      unsigned int x;
      
    bitcount_table() : 
      x(0) 
	{}
    };

  //==========================================================================================
  class BitManipulator
  {
  private:
    //----------------------------------------------------------------------------------------
    template<typename T>
    static T convert(const std::string & number, bool failIfLeftoverChars = true)
    {
      if(number.empty())
	return T(0);

      char c;
      T    x;

      std::istringstream i(number);

      if (!(i >> x) || (failIfLeftoverChars && i.get(c)))
	throw std::runtime_error(number);

      return x;
    } 
  
  public:

    //==========================================================================================
    //------------------------------------------------------------------------------------------
    //NOTE : This function is a helper function of double_to_binary. Input numbers are expected 
    //to be of the form : n >= 0
    static std::string integer_to_binary(unsigned int n)
    {
      int i = (8 * sizeof(unsigned int)), j = i;

      unsigned int stack[i];

      std::memset(stack, 0, sizeof(stack)/i);

      while(n)
      {
	stack[--i] = n % 2;
	n >>= 1;
      }

      std::string result;

      while(i < j)
      {
	if(stack[i++])
	  result.append("1");
	else
	  result.append("0");
      }

      return result;
    }

    //------------------------------------------------------------------------------------------
    //NOTE : This function is a helper function of double_to_binary. Input numbers are expected 
    //to be of the form : 0.0 <= d < 1.0
    static std::string decimal_to_binary(double d)
    {
      double epsilon(1e-6);

      std::string result;

      while(d > epsilon)
      {
	d *= 2.0;
	
	if(d >= 1.0)
	{
	  result.append("1");
	  d -= 1.0;
	}
	else
	{
	  result.append("0");
	}
      }

      return result;
    }

    //------------------------------------------------------------------------------------------
    //NOTE : This does NOT use the IEEE floating point notation represented by sign bit, mantissa
    //and exponent. This does a simple binary conversion (without regard to  sign for floating part).
    static std::string double_to_binary(const std::string& number)
    {
      size_t pos = number.find(".");
    
      int intPart = (pos != std::string::npos) ? convert<int>(number.substr(0, pos)) : convert<int>(number);
    
      std::string result = integer_to_binary(intPart);
    
      if(pos != std::string::npos)
	result.append(".").append(decimal_to_binary(convert<double>(number.substr(pos))));
      
      return result;
    }

    //------------------------------------------------------------------------------------------
    static unsigned int set_union(unsigned int a, unsigned int b)
    {
      return a | b;
    }

    //------------------------------------------------------------------------------------------
    static unsigned int set_intersection(unsigned int a, unsigned int b)
    {
      return a & b;
    }

    //------------------------------------------------------------------------------------------
    static unsigned int set_difference(unsigned int a, unsigned int b)
    {
      return a & ~b;
    }

    //------------------------------------------------------------------------------------------
    static unsigned int set_negation(unsigned int a)
    {
      //ALL_BITS_SET = ~0
      //cout << "^ = " << (~((unsigned int)0) ^ a) << endl;
      //return ~((unsigned int)0) ^ a;

      //cout << "~ = " << ~a << endl;
      return ~a;
    }

    //------------------------------------------------------------------------------------------
    static unsigned int set_bit(unsigned int a, unsigned int b)
    {
      return a | (0x01 << b);
    }

    //------------------------------------------------------------------------------------------
    static unsigned int reset_bit(unsigned int a, unsigned int b)
    {
      return a & ~(0x01 << b);
    }

    //------------------------------------------------------------------------------------------
    static unsigned int flip_bit(unsigned int a, unsigned int b)
    {
      return a ^ (0x01 << b);
    }

    //------------------------------------------------------------------------------------------
    static bool test_bit(unsigned int a, unsigned int b)
    {
      return (a & (0x01 << b)) != 0;
    }

    //Pre-compute a table for leading (trailing) zeroes
    //for each number between 0 and 255. Return the index
    //of the first (last) non-zero byte in the number
    //plus offset of zero bytes
    //------------------------------------------------------------------------------------------
    static unsigned int leading_one_bit(unsigned int a)
    {
      //Undefined for 0
      if(a == 0)
	return sizeof(unsigned int)*8 + 1;

      return sizeof(unsigned int)*8 - __builtin_clz(a) - 1;
    }

    //@!!!
    //------------------------------------------------------------------------------------------
    static unsigned int trailing_one_bit(unsigned int a)
    {
      //Undefined for 0
      if(a == 0)
	return sizeof(unsigned int)*8 + 1;

      //NOTE - Using the builtin count is ~4x faster
      //*
	return log2(a & ~(a - 1));
      /*/
	return __builtin_ctz(a);
      //*/
    }

    //@!!!
    //------------------------------------------------------------------------------------------
    static unsigned int reset_trailing_one_bit(unsigned int a)
    {
      return a & (a - 1);
    }

    //------------------------------------------------------------------------------------------
    static unsigned int Log2(unsigned int a)
    {
      return (a == 1) ? 0 : 1 + Log2(a >> 1);
    }

    // Only one bit is set. Find the position
    //------------------------------------------------------------------------------------------
    static unsigned int set_bit_pos(unsigned int a)
    {
      if(a == 0 || (a & (a - 1)) != 0)
	return -1;
      
      /*
	return log2(a);
	
     /*/
	
      //Calculate log
      
      return Log2(a);
      
      //*/
    }

    //@!
    // Gray code represenations of adjacent numbers differ from each other by one bit
    //------------------------------------------------------------------------------------------
    static unsigned int binary_to_gray(unsigned int a)
    {
      return (a >> 1) ^ a;
    }

    //------------------------------------------------------------------------------------------
    //Test results: Count 1s for 0 < i < 1e7
    //Count bits in O(b)  = 0m6.10s
    //Preset table of 256 = 0m4.15s
    //Built in bitcount   = 0m1.86s
    //------------------------------------------------------------------------------------------
    static unsigned int count_set_bits(unsigned int a)
    {
      /*
      //Count bit in O(b) time where b is # of 1 bits.	
      int count = 0;

      for(; a != 0; ++count, a = a & (a-1));
	
      return count;
      /*/
	
      //Hardware assisted bit counting
      //NOTE : Using the builtin count function is ~3.6X faster.
      return __builtin_popcount(a);
      //*/
    }

    //NOTE : Precomputing a table with number of ones for 256 
    //numbers is ~1.7x times faster.
    //------------------------------------------------------------------------------------------
    static void create_bit_count_table(int bitcount[256])
    {
      for(size_t i = 0; i < 256; ++i)
	bitcount[i] = __builtin_popcount(i);
    }

    //------------------------------------------------------------------------------------------
    static unsigned int count_set_bits(unsigned int a, const int bitcount[256])
    {
      unsigned int usize(sizeof(unsigned int));

      int count = 0;

      for(size_t i = 0; i < usize; ++i)
	count += bitcount[(a >> (8*i)) & 0xff];

      return count;
    }

    //------------------------------------------------------------------------------------------
    static unsigned int count_set_bits_tmp(unsigned int a)
    {
      //Find count
      unsigned int usize(sizeof(unsigned int));

      int count = 0;

      static bitcount_table<256> bt;

      for(size_t i = 0; i < usize; ++i)
	count += bt[(a >> (8*i)) & 0xff];

      return count;
    }

    //@!!
    // http://www.geeksforgeeks.org/count-total-set-bits-in-all-numbers-from-1-to-n/
    // Count the number of set bits of all numbers between 1 and n
    // - Linear count of each number. Runtime : O(nlgn)
    // - Each pattern of 0s and 1s from the last power of two is repeated twice in
    //   the count of the next power of two. 
    //   The first repeat of the pattern is preceeded by zeros and the next repeat
    //   of the pattern is preceeded by 1s 
    //   ie. n/2 0s followed by pattern of previous power of 2 and n/2 1s followed 
    //   by pattern of previous power of 2. 
    //   Note that we decrement the extra 1 bit counted for the power of two.
    //   Example: n( 1) = 1
    //            n( 2) = 1 + (n( 1) - 1) +  1 + (n( 1) - 1) =  2
    //            n( 4) = 1 + (n( 2) - 1) +  2 + (n( 2) - 1) =  5
    //            n( 8) = 1 + (n( 4) - 1) +  4 + (n( 4) - 1) = 13
    //            n(16) = 1 + (n( 8) - 1) +  8 + (n( 8) - 1) = 33
    //            n(32) = 1 + (n(16) - 1) + 16 + (n(16) - 1) = 81
    //   Runtime : O(lg n)
    //   @TODO : The following implementation does a linear count for values higher 
    //   than last power of two. This can be modified to break the number into its
    //   constituent powers of two and adding their number of 1s while accounting 
    //   for the extra 1 bits.
    //------------------------------------------------------------------------------------------    
    static size_t get_index(unsigned int n)
    {
      if(n < 4)
	return n;
      
      return log2(n) + 1;
    }

    /*
    //------------------------------------------------------------------------------------------
    unsigned int number_of_ones(unsigned int n)
    {
      vector<unsigned int> ones(get_index(n) + 1, 0);
      
      ones[1] = 1;
      
      for(size_t i = 2; i <= n; i *= 2)
	{
	  ones[get_index(i)] = 1 + 2*(ones[get_index(i/2)] - 1) + (i/2);
	  cout << "ones[" << get_index(i) << "] = " << ones[get_index(i)] << endl;
	}
      
      return ones.back();
    }
    */

    //------------------------------------------------------------------------------------------
    static unsigned int number_of_ones(unsigned int n)
    {
      int prev_ones = 1, next_ones;
      
      for(size_t i = 2; i <= n; i *= 2)
      {
	next_ones = 1 + 2*(prev_ones - 1) + (i/2);
	prev_ones = next_ones;
	
	std::cout << "ones[" << i << "] = " << next_ones << std::endl;
      }
      
      return next_ones;
    }

    //------------------------------------------------------------------------------------------
    static unsigned int mod_power_of_2(unsigned int a, unsigned int b)
    {
      //Get lower order bits
      return a & (b - 1);
    }

    //------------------------------------------------------------------------------------------
    static unsigned int next_power_of_2(unsigned int a)
    {
      if(a < 2)	return a + 1;
	
      //NOTE - Calculating next power of 2 from left shifting the 
      //leading one found by __builtin_clz() is about 8x faster than
      // calculating it by the method below.

      /*
	return (0x01 << leading_one_bit(a) + 1);      
      /*/
      
      int i = 2;
      
      do
      {
	i <<= 1;
      } while(i <= a);
      
      return i;

      //*/
    }

    //------------------------------------------------------------------------------------------
    static bool is_power_of_two(unsigned int n)
    {
      return (n & (n-1) == 0);
    }

    //Does the number have an even or odd number of 1s?
    //------------------------------------------------------------------------------------------
    static bool is_even_parity(unsigned int a)
    {
      //*
      //Count bit in O(b) time where b is # of 1 bits.	
      bool parity(true);
      
      for(; a != 0; a = a & (a-1))
	parity = !parity;
      
      return parity;
      /*/
      
      //Hardware assisted bit counting
      return (__builtin_popcount(a) % 2 == 0);
      //*/
    }

    //------------------------------------------------------------------------------------------
    static unsigned int set_bit(unsigned int a, unsigned int b, bool set)
    {
      if(set)
	return a | (0x01 << b);
      else 
	return a & ~(0x01 << b);
    }

    //------------------------------------------------------------------------------------------
    static unsigned int count_different_bits(unsigned int a, unsigned int b)
    {
      size_t count(0);

      for(unsigned int i = a^b; i != 0; i = (i & i - 1))
	++count;

      return count;
    }

    //------------------------------------------------------------------------------------------
    static unsigned int swap_even_odd_bits(unsigned int a)
    {
      /*
      size_t mask_even(0), mask_odd(0);

      size_t sizeint(sizeof(unsigned int));
    
      for(size_t i = 0; i < sizeint; ++i)
      {
	mask_odd  |= 0x55;
	mask_even |= 0xAA;
	
	if(i != sizeint - 1)
	{
	  mask_odd  <<= 8;
	  mask_even <<= 8;
	}
      }
    
      return (((mask_even & a) >> 1) | ((mask_odd & a) << 1 ));
      /*/
      
      int even_mask = 0b01010101, odd_mask = 0b10101010;
      //NOTE :         ^                      ^
      //               |                      |
      
      for(int i = sizeof(unsigned int) - 1; i > 0; --i)
      {
	even_mask |= (even_mask << 8);
	odd_mask  |= (odd_mask << 8);
      }
      
      //print_bits(even_mask);
      //print_bits(odd_mask);
      
      return ((a & even_mask) << 1) | ((a & odd_mask) >> 1);
      //*/
    }

    //----------------------------------------------------------------------------------------
    static void swap_numbers(int & a, int & b)
    {
      //Self swap will zero out number
      if(&a == &b)
	return;

      a = a ^ b;
      b = a ^ b;
      a = a ^ b;
    }

    //------------------------------------------------------------------------------------------
    //@BUGS
    /*
    static void copy_bits(unsigned int &rN, unsigned int M, unsigned int i, unsigned int j)
    {
      M <<= i;
    
      rN ^= M;
      rN |= M;
    }
    */

    //------------------------------------------------------------------------------------------
    static unsigned int create_mask(unsigned int a, int at_pos, int from_pos, int n)
    {
      unsigned int mask = 0;
      
      //Create mask from left most part
      for(size_t i = 0; i < n; ++i)
      {
	if(test_bit(a, from_pos + i))
	  mask = set_bit(mask, at_pos + i);
      }

      return mask;
    }

    //@!
    // Swap bit strip of length n between two non-overlapping positions in a number
    // Method 1 : Create bit masks of bit strips and swap using XOR
    //------------------------------------------------------------------------------------------
    static unsigned int swap_bits(unsigned int a, int p1, int p2, int n)
    {
      unsigned int size(8 * sizeof(unsigned int) - 1);
      
      //Check bounds and see if patterns overlap
      if(p1 > size || p2 > size || p1 > p2 || p1 + n - 1 >= p2)
	return -1;
      
      //Create mask from left part
      unsigned int mask = create_mask(a, p1, p2, n);
      
      //x = x ^ y
      a ^= mask;
      
      //Create mask from right part
      mask = create_mask(a, p2, p1, n);
      
      //y = x ^ y
      a ^= mask;
      
      mask = create_mask(a, p1, p2, n);	
      
      //x = x ^ y
      a ^= mask;
      
      return a;
    }

    // Method 2 : Check bit strips for differing bits. Flip differing bits.
    //------------------------------------------------------------------------------------------
    static unsigned int swap_bits_flip(unsigned int a, int p1, int p2, int n)
    {
      unsigned int size(8 * sizeof(unsigned int) - 1);
      
      //Check bounds and see if patterns overlap
      if(p1 > size || p2 > size || p1 > p2 || p1 + n - 1 >= p2)
	return -1;
      
      for(size_t i = 0; i < n; ++i)
      {
	//If the bits at the two positions are different, swap them
	if(test_bit(a, p1 + i) != test_bit(a, p2 + i))
	  {
	    a = flip_bit(a, p1 + i);
	    a = flip_bit(a, p2 + i);
	  }
      }
      
      return a;
    }

    //------------------------------------------------------------------------------------------
    static void print_bits(unsigned int a)
    {
      unsigned int leading_one_pos (a == 0 ? 0 : leading_one_bit(a));
      unsigned int mask            (a == 0 ? 0 : (0x01 << leading_one_pos));
      
      size_t zeros(a == 0 ? (8 * sizeof(unsigned int)) : (8 * sizeof(unsigned int)) - leading_one_pos - 1);
      for(size_t i = 0; i < zeros; ++i)
	std::cout << 0 << " ";
      
      while(mask)
      {
	std::cout << ((a & mask) != 0) << " ";
	mask >>= 1;
      }
      
      std::cout << std::endl;
    }


    //@!!
    // An efficient way to multiply a number is to find the nearest power of two and 
    // either add or subtract from the left shifted power of two value
    // For example:  7 x 5 = (7 << 3) + (7 x 1)
    //            : 13 x 3 = (13 << 3) - (13 x 1)
    //            :  7 x 6 = (7 << 3) - (7 x 2)
    //------------------------------------------------------------------------------------------
    static unsigned int multiply_closest_power_of_2(unsigned int a, unsigned int b)
    {
      if(a == 0 || b == 0)
	return 0;

      if(a == 1)
	return b;
      else if(b == 1)
	return a;

      if(a < b)
	std::swap(a, b);

      //If b is a multiple of 2
      if(b & (b - 1) == 0)
	return a << leading_one_bit(b);
	
      //Find next power of two
      int m = (0x01 << leading_one_bit(b) + 1);

      //Find closest power of two
      if((b - (m >> 1)) < (m - b))
	m >>= 1;

      //Save for addition or subtraction later
      //int offset = a * ((b > m) ? (b - m) : (m - b));
      int offset = a * (b - m);

      for(size_t i = 1; i < m; i <<= 1)
	a <<= 1;

      //Adjust positive or negarive offset depending
      //whether we choose previous or next power of two
      return a + offset;
    }
    
    //------------------------------------------------------------------------------------------
    static bool is_multiple_of_4(unsigned int a)
    {
      return (a & 0x3) == 0;
    }

    //@!
    // Find if a number is a multiple of three from bits.
    // Find difference in number of odd and even set bits.
    // Runtime : O(d) == O(lgn) 
    //------------------------------------------------------------------------------------------
    static bool is_multiple_of_3(int n)
    {
      if(n == 0)
	return true;

      if(n == 1)
	return false;

      if(n < 0)
	n = -n;

      int even_set(0), odd_set(0);

      bool even(true);

      while(n)
      {
	if(even && (n & 0x01))
	  even_set++;
	else if(!even && (n & 0x01))
	  odd_set++;
	
	even = !even;
	n >>= 1; 
      }

      return ((odd_set - even_set) % 3 == 0);
    }


    // Increment number by one without addition
    //------------------------------------------------------------------------------------------
    static unsigned int add_one(unsigned int a)
    {
      //@!
      //*
      //The two's complement is given by -a = ~a + 1
      //To get a + 1, simply get the negative of the negation of the number
	return -(~a);

      /*/
      int mask = 0x1;
      
      //Flip all ones until the first zero is found
      for(size_t i =0; i < (8 * sizeof(unsigned int)) && (mask & a); ++i)
      {
	a ^= mask;
	mask <<= 1;
      }
      
      return a ^ mask;
      //*/
    }


    // Add two numbers without arithmetic operations
    // Solution : The XOR of two numbers gives the sum without the carry over.
    // Get the carry over by the left shift of the AND of the two numbers.
    // Add the carry over until it is non-zero.
    //------------------------------------------------------------------------------------------
    static int add(int a, int b)
    {
      int sum = 0;
      
      while(b)
      {
	//Sum without carry
	sum = a ^ b;
	
	//Get carry over
	b   = (a & b) << 1;

	a   = sum;
      }
      
      return a;
    }

    //------------------------------------------------------------------------------------------
    static bool check_overflow(int a, int b)
    {
      //std::cout << "a = "<< a << ", b = "<< b << ", sum = " << a+b << std::endl;
      
      //NOTE : @!!!
      // (a > numeric_limits<int>::max() - b) is NOT the same as
      // (a + b > numeric_limits<int>::max()) !!!
      // Solution for both +ve numbers below
      //return(a > numeric_limits<int>::max() - b);
      
      if(a > 0 && b > 0)
	return (a+b < 0);
      else if(a < 0 && b < 0)
	return (a+b > 0);
      else
	return false;
    }

    // Find maximum without comparison of the numbers
    // IMP : Compare with ***0*** and NOT with 1
    //------------------------------------------------------------------------------------------
    static int find_max(int a, int b)
    {
      return ( (a - b) & (0x1 << (sizeof(int)*8 - 1)) ) == 0 ? a : b;
    }

    //------------------------------------------------------------------------------------------
    static int find_min(int a, int b)
    {
      return find_max(a, b) == b ? a : b;
    }

    //Get two's complement
    //------------------------------------------------------------------------------------------
    static int flip_sign(int a)
    {
      return ~a + 1;
    }

    // Find absolute value
    // IMP : Compare with ***0*** and NOT with 1
    //------------------------------------------------------------------------------------------
    static int find_abs(int a)
    {
      /*
	return ((0x1 << (sizeof(int)*8 - 1)) & a) == 0 ? a : flip_sign(a);
      /*/

      //@!!
      int mask = a >> (sizeof(int)*8 - 1);
      
      return (mask ^ a) - mask;

      //*/
    }

    //------------------------------------------------------------------------------------------
    static bool opposite_signs(int a, int b)
    {
      /*
      return (__builtin_clz(a) > 0) != (__builtin_clz(b) > 0);
      /*/
      return (a ^ b) < 0;
      //*/
    }

    //@!!
    //Cast to unsigned to ensure that sign bit is not copied over on left shift
    //------------------------------------------------------------------------------------------
    static int left_rotate_bits(int a, unsigned int r)
    {
      return 
	(static_cast<unsigned int>(a) << r) | 
	(static_cast<unsigned int>(a) >> (sizeof(unsigned int) * 8) - r);
    }

    //@!!
    //Cast to unsigned to ensure that sign bit is not copied over on left shift
    //------------------------------------------------------------------------------------------
    static int right_rotate_bits(int a, unsigned int r)
    {
      return
	(static_cast<unsigned int>(a) >> r) | 
	(static_cast<unsigned int>(a) << (sizeof(unsigned int) * 8) - r);
    }

    //------------------------------------------------------------------------------------------
    static int reverse_bits(int a)
    {
      size_t size(sizeof(int) * 8);
      
      for(size_t i = 0; i < size/2; ++i)
      {
	if(test_bit(a, i) != test_bit(a, size - i - 1))
	{
	  a = flip_bit(a, i);
	  a = flip_bit(a, size - i - 1);
	}
      }
      
      return a;
    }
    
    //@! 
    // Check Endianness
    // If the LAST byte is stored FIRST, it is LITTLE endian.
    //
    // Standard byte order for networks is big endian, also known as network byte order. 
    // Before transferring data on network, data is first converted to network byte 
    // order (big endian) with htons() or htonl().
    // http://www.geeksforgeeks.org/little-and-big-endian-mystery/
    //------------------------------------------------------------------------------------------
    static void find_endianness()
    {
      int n = 0x12345678;
      
      for(size_t i = 0; i < sizeof(int); ++i)
	printf(" %x", ((char *)&n)[i]);	
      std::cout << std::endl;

      
      int i = 1;
      char * c = (char*)(&i);
      
      if(*c == 1)
	std::cout << "Little endian " << std::endl;
      else
	std::cout << "Big endian " << std::endl;		
    }


    //@!!
    // Given an array of numbers where one element occurs once and every other one
    // appears thrice, find the number occuring once in O(n) time and O(1) space.
    // http://www.geeksforgeeks.org/find-the-element-that-appears-once/
    //
    // Solutions :
    // - Get the sum of all set bits modulo 3 from left to right. The number
    // occurring once is the one formed from the remainder of the modulo of bits.
    // Runtime : O(dn) and space O(1) where d is the number of bits
    // - Use the Radix sort partition step to separate numbers based on whether its
    // bit is set or unset going from right to left. Separate the lists and select
    // the list with size not a multiple of three ie. having the extra element.
    // Runtime : O(dn) and space O(1) where d is the number of bits
    //------------------------------------------------------------------------------------------
    static unsigned int find_unique_number(unsigned int arr[], int n)
    {
      unsigned int num = 0;
      
      for(int i = 8*sizeof(unsigned int) - 1; i >= 0; --i)
      {
	int sum = 0;
	
	for(int j = 0; j < n; ++j)
	{
	  if(test_bit(arr[j], i))		
	    sum++;
	}

	num |= (sum % 3);
	
	print_bits(num);
	
	if(i > 0)
	  num <<= 1;
      }

      return num;
    }

    //------------------------------------------------------------------------------------------
    static unsigned int find_unique_number_sort(unsigned int arr[], int n)
    {
      unsigned int num = 0, pos = 0, i = 0, j = n - 1;
      
      while((pos < 8*sizeof(unsigned int)) && (i < j))
      {
	int beg = i, end = j;
	
	//Partition by 0s and 1s
	while(i < j)
	{
	  while(i < j && !test_bit(arr[i], pos))
	    ++i;
	  
	  while(i < j && test_bit(arr[j], pos))
	    --j;
	  
	  if(i < j)
	  {
	    std::swap(arr[i], arr[j]);
	    
	    //NOTE : IMP! Increment counts else 
	    ++i;
	    --j;
	  }
	}
		
	//At this point i == j
	
	//i stepped into 1s
	if(test_bit(arr[i], pos))
	  --i;
		
	//j stepped into 0s
	if(!test_bit(arr[j], pos))
	  ++j;
	
	//Select first partition
	if((i - beg + 1) % 3)
	{
	  j = i;
	  i = beg;			
	}
	//Select second partition
	else
	{
	  i = j;
	  j = end;
	}
	
	++pos;		
      }

      return arr[i];
    }

    //@!
    // Case insensitive string compare
    //------------------------------------------------------------------------------------------
    static int compare_strings(const std::string & s1, const std::string & s2)
    {
      size_t min_len = std::min(s1.size(), s2.size()), max_len = std::max(s1.size(), s2.size()), i = 0;
      
      for(; i < min_len; ++i)
      {
	//Bit 5 (0 based) differs between a & A
	if((s1.at(i) != s2.at(i)) && (s1.at(i) != (s2.at(i) ^ (1 << 5))))
	  break;
      }

      //All characters compared
      if(i == min_len)
	return (min_len == max_len) ? 0 : (s1.size() < s2.size() ? -1 : 1);
      else
	//Convert both to lowercase
	return (s1.at(i) | (1 << 5)) < (s2.at(i) | (1 << 5)) ? -1 : 1;	
    }



  };

} // end namespace BitManip

#endif
