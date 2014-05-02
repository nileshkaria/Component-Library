#ifndef __SORT_H__
#define __SORT_H__

#include <algorithm>
#include <functional>
#include <stdexcept>
#include <vector>

//@TODO - Remove
#include <iostream>

namespace Sort
{
    template <typename T>
    bool Less(const T& lhs, const T& rhs)
    {
        return lhs < rhs;
    }
    
    //============================================================================
    //Selection Sort:
    //Linear number of exchanges.
    //Quadratic number of compare operations.
    //Worst case   : 1/2 N^2 
    //Average case : 1/2 N^2
    //Best case    : 1/2 N^2 
    //Running time does not depend upon the order of input.
    //Stability - NOT stable due to long distance exchange past equal item.
    //----------------------------------------------------------------------------    
    template<typename RandomAccessIterator>
      void selection_sort(RandomAccessIterator first, RandomAccessIterator last)
    {
        for(RandomAccessIterator i = first; i != last; ++i)
        {
            RandomAccessIterator min = i; 

            for(RandomAccessIterator j = i + 1; j != last; ++j)
            {
                if(Less(*j, *min))
                    min = j;
            }
            
            if(min != i)
	      std::swap(*i, *min);
        }
    }

    //----------------------------------------------------------------------------
    template<class RandomAccessIterator, class Compare>
      void selection_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
    {
      for(RandomAccessIterator i = first; i != last; ++i)
        {
            RandomAccessIterator min = i; 

            for(RandomAccessIterator j = i + 1; j != last; ++j)
            {
                if(comp(*j, *min))
                    min = j;
            }
            
            if(min != i)
	      std::swap(*i, *min);
        }      
    }

    //============================================================================
    //Insertion Sort:
    //Worst case   : 1/2 N^2 compares and 1/2 N^2 exchanges when input is reversed.
    //Average case : ~1/4 N^2 compares and ~1/4 N^2 exchanges. 
    //Best case    : N-1 compares and 0 exchanges when input is sorted.
    //Running time depends upon the order of input.
    //Number of exchanges is equal to number of inversions ie. the number of 
    //elements which are out of sequence. This is why insertion sort runs in 
    //linear time for partially sorted input with inversions <= cN.
    //Stability - Stable
    //----------------------------------------------------------------------------    
    template<typename RandomAccessIterator>
      void insertion_sort(RandomAccessIterator first, RandomAccessIterator last)
    {
        for(RandomAccessIterator i = first; i != last - 1; ++i)
        {
            for(RandomAccessIterator j = i + 1; j != first; --j)
            {
	      if(Less(*j, *(j-1)))
		std::swap(*j, *(j - 1));
            }
        }
    }

    //----------------------------------------------------------------------------
    template<class RandomAccessIterator, class Compare>
      void insertion_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
    {
      for(RandomAccessIterator i = first; i != last - 1; ++i)
        {
            for(RandomAccessIterator j = i + 1; j != first; --j)
            {
	      if(comp(*j, *(j - 1)))
		std::swap(*j, *(j - 1));
            }
        }      
    }

    //============================================================================
    //Shell Sort: 
    //Exchanges with larger increments creates nearly in order smaller subarrays. 
    //Worst case   : ?
    //Average case : ?
    //Best case    : N log3N compares for already sorted array with h = 3x + 1.
    //Since successive increment values of h differ by at least a factor of 3, 
    //there are ~log3N increment values. For each increment value h, the array is
    //already h-sorted so it will make ~N compares.
    //Worst case : 
    //Stability - NOT stable due to long distance exchange past equal item.
    //----------------------------------------------------------------------------    
    template<typename RandomAccessIterator>
      void shell_sort(RandomAccessIterator first, RandomAccessIterator last)
    {
      //Constant time complexity for RAIs
      int N = std::distance(first, last);
      
      int h = 1;
      while(h < N/3)
	h = 3*h + 1;

      while(h >= 1)
      {
        for(int i = h; i < N; ++i)
        {
	  //Compare elements h places apart and exchange if out of sequence.
	  for(int j = i; j >= h && Less(*(first + j), *(first + j - h)); j -= h)
	  {
	    std::swap(*(first + j), *(first + j - h));
	  }
        }
	
	//Decrement comparison distance
	h /= 3;
      }
    }

    //----------------------------------------------------------------------------
    template<class RandomAccessIterator, class Compare>
      void shell_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
    {
      //Constant time complexity for RAIs
      int N = std::distance(first, last);
      
      int h = 1;
      while(h < N/3)
	h = 3*h + 1;

      while(h >= 1)
      {
        for(int i = h; i < N; ++i)
        {
	  //Compare elements h places apart and exchange if out of sequence.
	  for(int j = i; j >= h && comp(*(first + j), *(first + j - h)); j -= h)
	  {
	    std::swap(*(first + j), *(first + j - h));
	  }
        }
	
	//Decrement comparison distance
	h /= 3;
      }
    }

    //============================================================================
    //============================================================================
    //============================================================================
    //Merge Sort:
    // Uses at most NlgN compares and 6NlgN array accesses to sort any array of 
    // size N
    // D(N) = 2D(N/2) + N for N > 1 with D(1) = 0, so D(N) = NlgN
    // Worst case   : NlgN
    // Average case : NlgN
    // Best case    : 1/2 NlgN compares. Merge sort is optimized 
    // to make ~N compares by checking and aborting merge if a[mid] <= a[mid + 1]
    // Stability - Stable sort. Note that the merge is done only if the first 
    // element of the right half is lesser than the last element of the left.
    //----------------------------------------------------------------------------
    template<typename T, typename Compare = std::less<T> >
      class MergeSort
      {
      private:
	//------------------------------------------------------------------------
	static void merge(std::vector<T> & v, std::vector<T> & aux, 
			  int lo, int mid, int hi)
	{
	  //Copy elements to aux array
	  for(int k = lo; k <= hi; ++k)
	    aux[k] = v[k];

	  int i = lo, j = mid + 1;

	  for(int k = lo; k <= hi; ++k)
	  {
	    //If left half is exhausted
	    if(i > mid)      
	      v[k] = aux[j++];
	    
	    //If right half is exhausted
	    else if(j > hi)  
	      v[k] = aux[i++];
	    
	    //Always pick the left element in case of equal elements
	    //to guarantee stable sort
	    else if(Compare()(aux[j], aux[i])) 
	      v[k] = aux[j++];
	    
	    else 
	      v[k] = aux[i++];
	  }
	}

	//------------------------------------------------------------------------    
	static void merge_sort(std::vector<T> & v, std::vector<T> & aux, int lo, int hi)
	{
	  if(hi <= lo)
	    return;
	  
	  int mid = (lo + hi)/2;
	  
	  merge_sort(v, aux, lo, mid);
	  merge_sort(v, aux, mid + 1, hi);	    

	  //Optimization step: Skip merge if last element of left half is less 
	  //than or equal to first element of right half
	  if(!Compare()(v[mid + 1], v[mid])) return;
	  
	  merge(v, aux, lo, mid, hi);
	}

      public:

	//========================================================================
	//Recursive Merge Sort:
	// Makes logarithmic number of recursive calls
	//------------------------------------------------------------------------    
	static void merge_sort(std::vector<T> & v)
	{
	  std::vector<T> aux(v.size());
	  
	  merge_sort(v, aux, 0, v.size() - 1);
	}

	//========================================================================
	//Bottom-up Merge Sort:
	// Makes logarithmic number of passes over the array and does not recurse
	//------------------------------------------------------------------------    
	static void bottom_up_merge_sort(std::vector<T> & v)
	{
	  int N = v.size();
	  std::vector<T> aux(N);

	  //Go over logarithmic number of sub-arrays
	  //                        ||
	  //                        \/ 
	  for(int sz = 1; sz < N; sz <<= 1)
	  {
	    //Traverse each sub-array
	    for(int lo = 0; lo < N - sz; lo += (sz << 1) )
	    {
	      //lo  = Left most element
	      //mid = One less than size of present sub-array
	      //hi  = Either the last element of sub-array or end of whole array
	      merge(v, aux, lo, lo + sz - 1, std::min(lo + (sz << 1) - 1, N - 1));
	    }
	  }
	}
      };


    //============================================================================
    //Quick Sort
    //Worst case   : Number of compares is ~1/2 N^2
    //Average case : Number of compares is ~1.39 NlgN 
    //               Number of exchanges is ~1/3 NlgN
    //Best case    : Number of compares is ~NlgN
    //Stability - NOT stable due to long distance exchange past equal item.
    //----------------------------------------------------------------------------    
    template<typename T, typename Compare = std::less<T> >
      class QuickSort
      {
      private:
        //If the partition is not stopped on equal keys, quick sort runs in 
        //quadratic time. This leads to ~NLgN compares on all equal keys.
        //------------------------------------------------------------------------
        static typename std::vector<T>::iterator partition(typename std::vector<T>::iterator lo, 
							   typename std::vector<T>::iterator hi)
        {
	  typename std::vector<T>::iterator i = lo;
	  typename std::vector<T>::iterator j = hi + 1;
	  
	  while(true)
	  {
	    //Increment until item to swap is found
	    while(Compare()(*(++i), *lo))
	      if(i == hi) break;
	    
	    //Decrement until item to swap is found
	    //Comparison with lo is redundant as j will equal lo to break loop
	    while(Compare()(*lo, *(--j)))
	      if(j == lo) break;
	    
	    //If pointers cross, elements are in expected partitions
	    if(i >= j) break;
	    
	    //*i < *j so we swap elements
	    std::swap(*i, *j);
	  }
	
	  //Swap pivot with last element of partition containing elements less than lo
	  std::swap(*lo, *j);
	  
	  return j;
	}
     
      //------------------------------------------------------------------------
      static void quick_sort(typename std::vector<T>::iterator lo, 
			     typename std::vector<T>::iterator hi)
        {
	  if(hi <= lo) return;

	  typename std::vector<T>::iterator mid = partition(lo, hi);
	  quick_sort(lo, mid - 1);
	  quick_sort(mid + 1, hi);
	}

      public:
        //------------------------------------------------------------------------
        static void quick_sort(std::vector<T> &v)
        {
	  //Return empty or one element arrays
	  if(v.empty() || v.size() == 1)
	    return;

	  //Shuffling needed for performance guarantee
	  std::random_shuffle(v.begin(), v.end());
	  
	  quick_sort(v.begin(), v.end() - 1);
	}

        //------------------------------------------------------------------------
        //Dijkstra's three way partitioning quicksort implementation is much faster 
        //in practice - linear in many practical applications - especially so when
        //the keys are non-distinct. 
        //The sorting lower bound is linear when only a constant number of keys are 
        //distinct. If all keys are distinct then a comparison based sorting lower 
        //bound is NlgN. This is given by :
        //lg(N!/ (x1! x2!...xn!)) ~= sigma(i=1 to n) [xi.lg(xi/N)] where there are 
        //n distinct keys and the ith one occurs xi times.
        static void three_way_partition_quick_sort(std::vector<T> &v, 
						   typename std::vector<T>::iterator lo,
						   typename std::vector<T>::iterator hi)
        {
	  if(hi <= lo) return;
	    
	  //Shuffling NOT needed here

	  typename std::vector<T>::iterator lt = lo;
	  typename std::vector<T>::iterator gt = hi;	  
	  typename std::vector<T>::iterator i  = lo;

	  //NOTE - All elements are compared against the pivot. If we want to find
	  //all duplicates equal to the pivot then we can do it in linear time with 
	  //one pass of the elements without recursing again. The duplicates will 
	  //be between the bounds lt and gt.
	  T pivot = *lo;
	  
	  //Say initial pivot = x
	  // |a|b|c|x|x|x|f|g|d|y|z|
	  //  |     |     |   |
	  //  lo    lt    i   gt
	  while(i <= gt)
	  {
	    //If v[i] is less than pivot, swap v[i] and v[lt] and increment both 
	    if(*i < pivot) std::swap(*i++, *lt++);
	    //If v[i] is more than pivot, swap v[i] and v[gt] and decrement gt 
	    else if(*i > pivot) std::swap(*i, *gt--);
	    //If v[i] is equal to the pivot, increment i only
	    else ++i;
	  }

	  //Sort v[lo, lt)
	  three_way_partition_quick_sort(v, lo, lt - 1);
	  
	  //Sort v[gt + 1, hi)
	  three_way_partition_quick_sort(v, gt + 1, hi);
	}

        //------------------------------------------------------------------------
        static const T & select(std::vector<T> &v, int rank)
        {
	  //Shuffling needed for performance guarantee
	  //NOTE - Instead of shuffling, one could use Tukey's ninther to find a 
	  //random element where three sets of consecutive three - nine elements -
	  //are selected at random and the median of the medians of these sets is 
	  //used to partition the array. This uses at most 12 compares.
	  std::random_shuffle(v.begin(), v.end());
	  
	  typename std::vector<T>::iterator lo = v.begin();
	  typename std::vector<T>::iterator hi = v.end() - 1;

	  while(hi > lo)
	  {
	    typename std::vector<T>::iterator mid = partition(lo, hi);
	    
	    int d = std::distance(lo, mid);

	    if(d < rank)         lo = mid + 1;
	    else if(d > rank)    hi = mid - 1;
	    else return *mid;
	  }
	  
	  //hi == lo ie. one element 
	  return *(v.begin());
	}
      
      };

    //============================================================================
    // Applications of Priority Queues:
    //
    //   - Event-driven simulation. [customers in a line, colliding particles]
    //   - Numerical computation. [reducing roundoff error]
    //   - Data compression. [Huffman codes]
    //   - Graph searching. [Dijkstra's algorithm, Prim's algorithm]
    //   - Number theory. [sum of powers]
    //   - Artificial intelligence. [A* search]
    //   - Statistics. [maintain largest M values in a sequence, find outliers]
    //   - Operating systems. [load balancing, interrupt handling]
    //   - Discrete optimization. [bin packing, scheduling]
    //   - Spam filtering. [Bayesian spam filter]
    
    // Binary heap
    // Impossible to find max, delete max and insert in constant time
    // Binary heap:
    // Insert     - lgN
    // Delete max - lgN
    // Find max   - O(1)

    //Heap construction : Number of compares and exchanges <= 2N
    //Heapsort
    //Worst case   : Number of compares and exchanges is <= 2NlgN
    //Average case : Number of compares and exchanges is <= 2NlgN
    //Best case    : Number of compares and exchanges is <= 2NlgN
    //Stability - NOT stable though offers in-place sorting without extra space.
    //Notes : Inner loop longer than Quicksort and poor use of cache memory due 
    //to long range swaps.
    //----------------------------------------------------------------------------
    template<typename T>
      class Heapsort
      {
      private:
	T *       _array;
	size_t    _size;
	size_t    _capacity;

	//------------------------------------------------------------------------
	Heapsort(const Heapsort&);
	Heapsort& operator=(const Heapsort&);

	//------------------------------------------------------------------------
	bool less(int lhs, int rhs)
	{
	  return _array[lhs - 1] < _array[rhs - 1];
	}

	//------------------------------------------------------------------------
	void swap(int lhs, int rhs)
	{
	  std::swap(_array[lhs - 1], _array[rhs - 1]);
	}

	//------------------------------------------------------------------------
	void swim(int k)
	{
	  //Swim until we reach the root
	  while(k > 1 && less(k/2, k))
	  {
	    swap(k, k/2);
	    k /= 2;
	  }
	}

	//------------------------------------------------------------------------
	void sink(int k, int heapSize)
	{
	  //Sink until we reach a leaf node
	  while((k << 1) <= heapSize)
	  {
	    int j = k << 1;
	    
	    //Find larger of the two children
	    //to maintain heap invariant
	    if(j < heapSize && less(j, j + 1)) ++j;
	
	    //Find largest amongst three
	    if(!less(k, j)) break;
	    
	    swap(k, j);
	    k = j;
	  }
	}

	//------------------------------------------------------------------------
	void resize(int capacity)
	{
	  T * temp = new T[capacity];
	  
	  //@NOTE - Use std::copy() instead of memcpy() here. It is
	  //faster and compilers will optimize to memcpy().
	  //http://stackoverflow.com/questions/4707012/c-memcpy-vs-stdcopy/9980859#9980859
	  //memcpy(temp, _array, _size*sizeof(T));
	  
	  std::copy(&_array[0], &_array[_size], &temp[0]);
	  
	  delete [] _array;
	  
	  _array   = temp;
	  _capacity = capacity;
	} 

      public:
	//------------------------------------------------------------------------
      Heapsort() :
	_array     (new T[1]),
        _size      (0),
	_capacity  (1)
	{}

	//------------------------------------------------------------------------
	~Heapsort()
	{
	  delete [] _array;
	}

	//------------------------------------------------------------------------
	void insert(const T& t)
	{
	  if(_size == _capacity)
	    resize(_size << 1);

	  _array[_size++] = t;

	  swim(_size);
	}

	//------------------------------------------------------------------------
	const T & getMax() const
	{
	  return _array[0];
	}

	//------------------------------------------------------------------------
	//At most 2lgN compares to sink root 
	T deleteMax()
	{
	  if(!_size)
	    throw std::runtime_error("Heapsort : Empty heap");

	  T temp = _array[0];

	  swap(1, _size--);

	  if(_size == (_capacity >> 2))
	    resize(_size >> 1);

	  sink(1, _size);

	  return temp;
	}

	//------------------------------------------------------------------------
	const T & operator[](size_t i) const
	{
	  return _array[i];
	}

	//------------------------------------------------------------------------
	T & operator[](size_t i)
	{
	  return _array[i];
	}

	//------------------------------------------------------------------------
	bool isEmpty() const
	{
	  return _size == 0;
	}

	//------------------------------------------------------------------------
	size_t size() const
	{
	  return _size;
	}

	//------------------------------------------------------------------------
	void sort()
	{
	  int N = _size;

	  //Heap construction uses <=2N compares and exchanges
	  for(int k = N/2; k >= 1; --k)
	    sink(k, N);

	  while(N > 1)
	  {
	    //Swap largest element with the last one in the present bounds
	    swap(1, N);

	    //Sink newly added root to its right position
	    sink(1, --N);
	  }	    
	}

      };

}
 

#endif
