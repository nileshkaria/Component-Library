#include "bitmanip.h"

#include <limits>

using namespace std;
using namespace BitManip;

void test_trailing_one_bit()
{
  /*
    Using builtin count - 

    real	0m13.19s
    user	0m8.35s
    sys	0m0.02s

    Using log2(a & ~(a-1)) -

    real	0m43.41s
    user	0m39.86s
    sys	0m0.04s
  */

  for(size_t i = 0; i < 64; ++i)
    cout << "Trailing bit = " << i << " = " << BitManipulator::trailing_one_bit(i) << endl;

  for(size_t i = 0; i < 1e9; ++i)
    BitManipulator::trailing_one_bit(i);
}

void test_count_set_bits()
{
  /*
    Using builtin count - 
    real	0m21.77s
    user	0m19.63s
    sys	0m0.02s
    
    Using pre-computed table:
    real	0m46.32s
    user	0m41.59s
    sys	0m0.03s
    
    Using pre-computed TMP table:
    real	0m42.05s
    user	0m42.04s
    sys	0m0.00s
    
    Counting ones by checking a & (a-1) until a > 0:
    real	1m19.46s
    user	1m10.75s
    sys	0m0.06s
  */
	
    /*
    for(size_t i = 0; i < 64; ++i)
    cout << "Set bits = " << i << " = " << count_set_bits(i) << endl;

    for(size_t i = 0; i < 1e9; ++i)
    count_set_bits(i);	
    
    /*/

  static int bitcount[256] = {};
  
  BitManipulator::create_bit_count_table(bitcount);
 
  for(size_t i = 0; i < 64; ++i)
    cout << "Set bits = " << i << " = " << BitManipulator::count_set_bits_tmp(i) << endl;

  for(size_t i = 0; i < 1e9; ++i)
    BitManipulator::count_set_bits(i, bitcount);	

  //*/
}

void test_multiply_closest_power_of_2()
{
  cout << "13 x 3 = " << BitManipulator::multiply_closest_power_of_2(13, 3) << endl;
  
  for(size_t i = 1; i <= 12; ++i)
    cout << i << " x 16 = " << BitManipulator::multiply_closest_power_of_2(i, 16) << endl;
}

void test_multiple_of_4()
{
  for(size_t i = 0; i <= 128; ++i)
    if(BitManipulator::is_multiple_of_4(i))
      cout << "i = " << i << " is multiple of 4" << endl;
}

void test_is_multiple_of_3()
{
  for(size_t i = 0; i < 64; i++)
  {
    cout << i << " is multiple of 3? " << boolalpha << BitManipulator::is_multiple_of_3(i) << endl;
  }
}

void test_next_power_of_2()
{
  /*
    Using builtin count - 
    real	0m15.52s
    user	0m13.56s
    sys	0m0.03s
    
    Finding next power of two by left shift - 
    real	1m46.22s
    user	1m39.43s
    sys	0m0.11s
  */

  for(size_t i = 0; i < 64; ++i)
    cout << "Next power of " << i << " = " << BitManipulator::next_power_of_2(i) << endl;
  
  for(size_t i = 0; i < 1e9; ++i)
    BitManipulator::next_power_of_2(i);
}

void test_is_even_parity()
{
  for(size_t i = 0; i < 64; i++)	
    cout << "i = " << i << " has even parity? " << boolalpha << BitManipulator::is_even_parity(i) << endl;
}

void test_print_bits()
{
  for(size_t i = 0; i < 128; i += 7)
  {
    cout << i << " = " << endl;
    BitManipulator::print_bits(i);
  }
}

void test_reset_trailing_one_bit()
{
  for(size_t i = 0; i < 64; ++i)
  {
    cout << "--------------------------" << endl;		
    BitManipulator::print_bits(i);
    BitManipulator::print_bits(BitManipulator::reset_trailing_one_bit(i));
    cout << "--------------------------" << endl;
  }
}

void test_binary_to_gray()
{
  for(size_t i = 0; i < 65; ++i)
  {
    cout << "i = " << i << endl;
    cout << "----------------------------------------------------------------------" << endl;
    //BitManipulator::print_bits(i);
    BitManipulator::print_bits(BitManipulator::binary_to_gray(i));
    cout << "----------------------------------------------------------------------" << endl;
  }
}

void test_add_one()
{
  for(size_t i = 0; i < 65; ++i)
  {
    if(BitManipulator::add_one(i) != i + 1)
    {
      cout << "i = " << i << endl;
      cout << "----------------------------------------------------------------------" << endl;
      BitManipulator::print_bits(i);
      BitManipulator::print_bits(BitManipulator::add_one(i));
      cout << "----------------------------------------------------------------------" << endl;
    }
  }
}

void test_add()
{
  cout << "15 + 1 = " << BitManipulator::add(15, 1) << endl;
  cout << "1 + 15 = " << BitManipulator::add(1, 15) << endl;
  
  cout << "14 + 1 = " << BitManipulator::add(14, 1) << endl;
  cout << "1 + 14 = " << BitManipulator::add(1, 14) << endl;

  cout << "-15 + 1 = " << BitManipulator::add(-15, 1) << endl;
  cout << "-1 + 15 = " << BitManipulator::add(-1, 15) << endl;
  
  cout << "14 - 1 = " << BitManipulator::add(14, -1) << endl;
  cout << "1 - 14 = " << BitManipulator::add(1, -14) << endl;
}

void test_check_overflow()
{
  int a = numeric_limits<int>::min() + 1, b = numeric_limits<int>::max();
  cout << boolalpha <<BitManipulator::check_overflow(a, 0) << endl;
  cout << boolalpha <<BitManipulator::check_overflow(a, -1) << endl;
  cout << boolalpha <<BitManipulator::check_overflow(a, -2) << endl;
  cout << boolalpha <<BitManipulator::check_overflow(a - 1, b) << endl;
  cout << boolalpha <<BitManipulator::check_overflow(a - 1, -b) << endl;
  cout << boolalpha <<BitManipulator::check_overflow(-a, b) << endl;
}

void test_find_max_min()
{
  /*
    int a = numeric_limits<int>::min() + 1;
    cout << check_overflow(a, 0) << endl;
    cout << check_overflow(a, -1) << endl;
    cout << check_overflow(a, -2) << endl;
  */

  cout << "Max = " << BitManipulator::find_max(-10, -20) << endl;
  cout << "Max = " << BitManipulator::find_max(-20, -10) << endl;

  cout << "Max = " << BitManipulator::find_max(20, 10) << endl;
  cout << "Max = " << BitManipulator::find_max(10, 20) << endl;

  cout << "Max = " << BitManipulator::find_max(0, 20) << endl;
  cout << "Max = " << BitManipulator::find_max(20, 0) << endl;

  cout << "Max = " << BitManipulator::find_max(-1, 20) << endl;
  cout << "Max = " << BitManipulator::find_max(20, -1) << endl;

  cout << "--------------------------" << endl;

  cout << "Min = " << BitManipulator::find_min(-10, -20) << endl;
  cout << "Min = " << BitManipulator::find_min(-20, -10) << endl;

  cout << "Min = " << BitManipulator::find_min(20, 10) << endl;
  cout << "Min = " << BitManipulator::find_min(10, 20) << endl;

  cout << "Min = " << BitManipulator::find_min(0, 20) << endl;
  cout << "Min = " << BitManipulator::find_min(20, 0) << endl;

  cout << "Min = " << BitManipulator::find_min(-1, 20) << endl;
  cout << "Min = " << BitManipulator::find_min(20, -1) << endl;

  cout << "--------------------------" << endl;

  int a = numeric_limits<int>::min() + 1;

  cout << "Max = " << BitManipulator::find_max(a, 0) << endl;
  cout << "Max = " << BitManipulator::find_max(0, a) << endl;

  cout << "Max = " << BitManipulator::find_max(a, -1) << endl;
  cout << "Max = " << BitManipulator::find_max(-1, a) << endl;

  cout << "Max = " << BitManipulator::find_max(a, -2) << endl;
  cout << "Max = " << BitManipulator::find_max(-2, a) << endl;

  //NOTE: Underflow and overflow occur for these cases
  /*		
                cout << "Max = " << BitManipulator::find_max(a, 1) << endl;
                cout << "Max = " << BitManipulator::find_max(1, a) << endl;

                cout << "Max = " << BitManipulator::find_max(a, 2) << endl;
                cout << "Max = " << BitManipulator::find_max(2, a) << endl;
  */

  cout << "Min = " << BitManipulator::find_min(a, 0) << endl;
  cout << "Min = " << BitManipulator::find_min(0, a) << endl;

  cout << "Min = " << BitManipulator::find_min(a, -1) << endl;
  cout << "Min = " << BitManipulator::find_min(-1, a) << endl;

  cout << "Min = " << BitManipulator::find_min(a, -2) << endl;
  cout << "Min = " << BitManipulator::find_min(-2, a) << endl;
}

void test_find_abs()
{	
  cout << "Abs = " << BitManipulator::find_abs(BitManipulator::find_max(-10, -20)) << endl;
  cout << "Abs = " << BitManipulator::find_abs(BitManipulator::find_max(-20, -10)) << endl;

  cout << "Abs = " << BitManipulator::find_abs(BitManipulator::find_max(20, 10)) << endl;
  cout << "Abs = " << BitManipulator::find_abs(BitManipulator::find_max(10, 20)) << endl;

  cout << "Abs = " << BitManipulator::find_abs(BitManipulator::find_max(0, 20)) << endl;
  cout << "Abs = " << BitManipulator::find_abs(BitManipulator::find_max(20, 0)) << endl;

  cout << "Abs = " << BitManipulator::find_abs(BitManipulator::find_max(-1, 20)) << endl;
  cout << "Abs = " << BitManipulator::find_abs(BitManipulator::find_max(20, -1)) << endl;

  cout << "--------------------------" << endl;

  cout << "Abs = " << BitManipulator::find_abs(BitManipulator::find_min(-10, -20)) << endl;
  cout << "Abs = " << BitManipulator::find_abs(BitManipulator::find_min(-20, -10)) << endl;

  cout << "Abs = " << BitManipulator::find_abs(BitManipulator::find_min(20, 10)) << endl;
  cout << "Abs = " << BitManipulator::find_abs(BitManipulator::find_min(10, 20)) << endl;

  cout << "Abs = " << BitManipulator::find_abs(BitManipulator::find_min(0, 20)) << endl;
  cout << "Abs = " << BitManipulator::find_abs(BitManipulator::find_min(20, 0)) << endl;

  cout << "Abs = " << BitManipulator::find_abs(BitManipulator::find_min(-1, 20)) << endl;
  cout << "Abs = " << BitManipulator::find_abs(BitManipulator::find_min(20, -1)) << endl;

  cout << "--------------------------" << endl;

  int a = numeric_limits<int>::min() + 1;

  cout << "Abs = " << BitManipulator::find_abs(BitManipulator::find_max(a, 0)) << endl;
  cout << "Abs = " << BitManipulator::find_abs(BitManipulator::find_max(0, a)) << endl;

  cout << "Abs = " << BitManipulator::find_abs(BitManipulator::find_max(a, -1)) << endl;
  cout << "Abs = " << BitManipulator::find_abs(BitManipulator::find_max(-1, a)) << endl;

  cout << "Abs = " << BitManipulator::find_abs(BitManipulator::find_max(a, -2)) << endl;
  cout << "Abs = " << BitManipulator::find_abs(BitManipulator::find_max(-2, a)) << endl;

  cout << "Abs = " << BitManipulator::find_abs(BitManipulator::find_min(a, 0)) << endl;
  cout << "Abs = " << BitManipulator::find_abs(BitManipulator::find_min(0, a)) << endl;

  cout << "Abs = " << BitManipulator::find_abs(BitManipulator::find_min(a, -1)) << endl;
  cout << "Abs = " << BitManipulator::find_abs(BitManipulator::find_min(-1, a)) << endl;

  cout << "Abs = " << BitManipulator::find_abs(BitManipulator::find_min(a, -2)) << endl;
  cout << "Abs = " << BitManipulator::find_abs(BitManipulator::find_min(-2, a)) << endl;
}

void test_rotate_bits()
{
  BitManipulator::print_bits(37);
  BitManipulator::print_bits(BitManipulator::left_rotate_bits(37, 3));
  BitManipulator::print_bits(BitManipulator::right_rotate_bits(37, 3));
  
  cout << "--------------------------" << endl;
  
  BitManipulator::print_bits(63);
  BitManipulator::print_bits(BitManipulator::left_rotate_bits(63, 5));
  BitManipulator::print_bits(BitManipulator::right_rotate_bits(63, 5));
  
  cout << "--------------------------" << endl;
  
  BitManipulator::print_bits(-5);
  BitManipulator::print_bits(BitManipulator::left_rotate_bits(-5, 4));
  BitManipulator::print_bits(BitManipulator::right_rotate_bits(-5, 4));
  
  cout << "--------------------------" << endl;
}

void test_reverse_bits()
{
  BitManipulator::print_bits(37);
  BitManipulator::print_bits(BitManipulator::reverse_bits(37));

  cout << "--------------------------" << endl;

  BitManipulator::print_bits(63);
  BitManipulator::print_bits(BitManipulator::reverse_bits(63));

  cout << "--------------------------" << endl;

  BitManipulator::print_bits(-5);
  BitManipulator::print_bits(BitManipulator::reverse_bits(-5));
}

void test_endianness()
{
  BitManipulator::find_endianness();
}

void test_swap_bits()
{
  BitManipulator::print_bits(47);
  BitManipulator::print_bits(BitManipulator::swap_bits(47, 1, 5, 3));
  BitManipulator::print_bits(BitManipulator::swap_bits_flip(47, 1, 5, 3));

  cout << "--------------------------" << endl;

  BitManipulator::print_bits(28);
  BitManipulator::print_bits(BitManipulator::swap_bits(28, 0, 3, 2));
  BitManipulator::print_bits(BitManipulator::swap_bits_flip(28, 0, 3, 2));
  
  cout << "--------------------------" << endl;
  
  BitManipulator::print_bits(15);
  BitManipulator::print_bits(BitManipulator::swap_bits(15, 0, 4, 4));
  BitManipulator::print_bits(BitManipulator::swap_bits_flip(15, 0, 4, 4));
  
  cout << "--------------------------" << endl;
}

void test_swap_even_odd_bits()
{
  BitManipulator::print_bits(1111);
  BitManipulator::print_bits(BitManipulator::swap_even_odd_bits(1111));
}

void test_swap_numbers()
{
  int a = 10, b = -15;
  
  cout << "a = " << a << " & b = " << b << endl;	
  BitManipulator::swap_numbers(a, b);
  cout << "a = " << a << " & b = " << b << endl;
  
  a = numeric_limits<int>::min(), b = numeric_limits<int>::max();
  
  cout << "a = " << a << " & b = " << b << endl;	
  BitManipulator::swap_numbers(a, b);
  cout << "a = " << a << " & b = " << b << endl;
}

void test_number_of_ones()
{
  cout << "Ones in 128 = " << BitManipulator::number_of_ones(128) << endl;
}

void test_opposite_signs()
{
  cout << 16 << " " << 0 << " " << boolalpha << BitManipulator::opposite_signs(16, 0) << endl;
  cout << -16 << " " << 0 << " " << boolalpha << BitManipulator::opposite_signs(-16, 0) << endl;
  cout << -16 << " " << 10 << " " << boolalpha << BitManipulator::opposite_signs(-16, 10) << endl;
  cout << -16 << " " << -10 << " " << boolalpha << BitManipulator::opposite_signs(-16, -10) << endl;
}

void test_find_unique_number()
{
  //unsigned int a[] = {12, 1, 12, 12, 3, 1, 1, 2, 3, 3};
  unsigned int a[] = {12, 10, 12, 12, 10, 10, 8, 8, 16, 8};
  
  //cout << "Unique number = " << BitManipulator::find_unique_number(a, sizeof(a)/sizeof(unsigned int)) << endl;
  cout << "Unique number = " << BitManipulator::find_unique_number_sort(a, sizeof(a)/sizeof(unsigned int)) << endl;
}

void test_compare_string()
{
  cout << "Comparing " << BitManipulator::compare_strings("Dijkstra", "dijkstra" ) << endl;
  cout << "Comparing " << BitManipulator::compare_strings("Turing", "tur" ) << endl;
  cout << "Comparing " << BitManipulator::compare_strings("wick", "Sedgewick" ) << endl;
  cout << "Comparing " << BitManipulator::compare_strings("sedge", "Sedgewick" ) << endl;
}

void test_set_bit_pos()
{
  cout << "Set bit " << BitManipulator::set_bit_pos(0)   << endl;
  cout << "Set bit " << BitManipulator::set_bit_pos(12)  << endl;
  cout << "Set bit " << BitManipulator::set_bit_pos(-12) << endl;
  cout << "Set bit " << BitManipulator::set_bit_pos(1)   << endl;
  cout << "Set bit " << BitManipulator::set_bit_pos(16)  << endl;
}


int main()
{
  /*
  cout << BitManipulator::double_to_binary("256.126") << endl;

  cout << BitManipulator::count_different_bits(27, 13) << endl;

  cout << BitManipulator::next_power_of_2(27) << endl;
  cout << BitManipulator::next_power_of_2(13) << endl;

  BitManipulator::BitManipulator::print_bits(27);
  BitManipulator::BitManipulator::print_bits(13);
  
  for(size_t i = 0; i < sizeof(unsigned int) * 8; i++)
  {
    unsigned int u = (0x01 << i);
    cout << "Leading 1 bit for " << u << " = " << BitManipulator::leading_one_bit(u) <<  ", leading zero = " << __builtin_clz(u) << endl;
  }
  */

  /*
  for(size_t i = 0; i < sizeof(unsigned int) * 8; i++)
    //cout << "Next power of 2 for " << i << " = " <<
    //BitManipulator::next_power_of_2(i) << endl;
    BitManipulator::next_power_of_2(i);
  */
  
  /*
  for(size_t i = 0; i < 1e9; i++)
    BitManipulator::next_power_of_2(i);
  */
  
  //test_next_power_of_2();
	
  //test_print_bits();

  //test_is_multiple_of_3();

  //test_is_even_parity();

  //test_count_set_bits();

  //test_multiply_closest_power_of_2();
  
  //test_trailing_one_bit();

  //test_check_overflow();

  //test_endianness();

  //test_reverse_bits();

  //test_rotate_bits();

  //test_find_max_min();

  //test_find_abs();

  //test_multiple_of_4();

  //test_reset_trailing_one_bit();
  
  //test_binary_to_gray();

  //test_add_one();

  //test_swap_bits();

  //test_add();

  //test_number_of_ones();

  //test_opposite_signs();

  //test_find_unique_number();

  //test_compare_string();

  //test_swap_even_odd_bits();

  //test_set_bit_pos();

  //test_swap_numbers();
  
  return 0;  
}
