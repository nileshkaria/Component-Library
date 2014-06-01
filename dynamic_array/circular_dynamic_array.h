#ifndef __CIRCULAR_DYNAMIC_ARRAY__
#define __CIRCULAR_DYNAMIC_ARRAY__

//#include <iterator>
//#include <iostream>
#include <algorithm>
#include <cstring>
#include <utility>

//====================================================================================================
//====================================================================================================
namespace DynamicArray
{

  //==================================================================================================
  //==================================================================================================
  template <typename T>
  class dynamic_array
  {
  private:
    //------------------------------------------------------------------------------------------------
    friend class iterator;
		
    size_t    _capacity;
    size_t    _front;
    size_t    _back;

    T        *_array;
	
    //------------------------------------------------------------------------------------------------
    void resize(size_t size);

    //------------------------------------------------------------------------------------------------
    int next_power_of_2(int n);

    //------------------------------------------------------------------------------------------------
    int relative_index(int i);

  public:

    //================================================================================================
    //================================================================================================
    class iterator // : public std::iterator<std::input_iterator_tag, T>
    {
    private:
      //----------------------------------------------------------------------------------------------
      friend class dynamic_array;

      static const int       LeftSentinel;
      static const int       RightSentinel;

      dynamic_array<T>     *_pDA;
      int                   _pos;

    public:
      //----------------------------------------------------------------------------------------------
      iterator(dynamic_array<T> * pDA = NULL, int pos = iterator::RightSentinel) :
      _pDA (pDA),
	_pos (pos)
	{}

      //----------------------------------------------------------------------------------------------
      ~iterator() {}

      //----------------------------------------------------------------------------------------------
      iterator(const iterator &rhs) :
      _pDA (rhs._pDA),
	_pos (rhs._pos)
	  {}
      
      //----------------------------------------------------------------------------------------------
      iterator operator=(const iterator &rhs) 
      {
	if(&rhs != this)
	{
	  //Shallow copy
	  _pDA = rhs._pDA;
	  _pos = rhs._pos;
	}
	
	return *this;
      }
      
      //----------------------------------------------------------------------------------------------
      iterator & operator++()
      {
	if(_pos != iterator::RightSentinel)
	{
	  if(_pos == iterator::LeftSentinel)
	    _pos = _pDA->_front;
	  else
	    ++_pos;
	  
	  if(_pos == _pDA->_back)
	    _pos = iterator::RightSentinel;
	}
	
	return *this;
      }
      
      //----------------------------------------------------------------------------------------------
      iterator operator++(int)
      {
	iterator tmp(*this);
	
	operator++();
	
	return tmp;
      }
      
      //----------------------------------------------------------------------------------------------
      iterator & operator--()
      {
	if(_pos != iterator::LeftSentinel)
	{
	  if(_pos == iterator::RightSentinel)
	    _pos = _pDA->_back - 1;
	  else
	    --_pos;
	  
	  if(_pos < _pDA->_front)
		  _pos = iterator::LeftSentinel;
	}
	
	return *this;
      }
      
      //----------------------------------------------------------------------------------------------
      iterator operator--(int)
      {
	iterator tmp(*this);
	
	operator--();
	
	return tmp;
      }
      
      //----------------------------------------------------------------------------------------------
      bool operator==(const iterator &rhs) 
      {
	return (rhs._pos == _pos);
      }
      
      //----------------------------------------------------------------------------------------------
      bool operator!=(const iterator &rhs) 
      {
	return !(rhs._pos == _pos);
      }
      
      //----------------------------------------------------------------------------------------------
      T & operator*()
      {
	return _pDA->_array[_pDA->relative_index(_pos)];
      }

      //----------------------------------------------------------------------------------------------
      const T & operator*() const
      {
	return _pDA->_array[_pDA->relative_index(_pos)];
      }

    };

    //================================================================================================
    //================================================================================================
    class reverse_iterator // : public std::iterator<std::input_iterator_tag, T>
    {
    private:
      dynamic_array<T>     *_pDA;
      int                   _pos;

    public:
      //----------------------------------------------------------------------------------------------
      reverse_iterator(dynamic_array<T> * pDA = NULL, int pos = iterator::LeftSentinel) :
      _pDA (pDA),
	_pos (pos)
	{}

      //----------------------------------------------------------------------------------------------
      ~reverse_iterator() {}

      //----------------------------------------------------------------------------------------------
      reverse_iterator(const reverse_iterator &rhs) :
      _pDA (rhs._pDA),
	_pos (rhs._pos)
	  {}

      //----------------------------------------------------------------------------------------------
      reverse_iterator operator=(const reverse_iterator &rhs) 
      {
	if(&rhs != this)
	{
	  //Shallow copy
	  _pDA = rhs._pDA;
	  _pos = rhs._pos;
	}
	
	return *this;
      }

      //----------------------------------------------------------------------------------------------
      reverse_iterator & operator++()
      {
	if(_pos != iterator::LeftSentinel)
	{
	  if(_pos == iterator::RightSentinel)
	    _pos = _pDA->_back - 1;
	  else
	    --_pos;
	  
	  if(_pos < _pDA->_front)
	    _pos = iterator::LeftSentinel;
	}
	
	return *this;
      }

      //----------------------------------------------------------------------------------------------
      reverse_iterator operator++(int)
      {
	reverse_iterator tmp(*this);

	operator++();
			
	return tmp;
      }

      //----------------------------------------------------------------------------------------------
      reverse_iterator & operator--()
      {
	if(_pos != iterator::RightSentinel)
	{
	  if(_pos == iterator::LeftSentinel)
	    _pos = _pDA->_front;
	  else
	    ++_pos;
	  
	  if(_pos == _pDA->_back)
	    _pos = iterator::RightSentinel;
	}
	
	return *this;
      }

      //----------------------------------------------------------------------------------------------
      reverse_iterator operator--(int)
      {
	reverse_iterator tmp(*this);
	
	operator--();
			
	return tmp;
      }

      //----------------------------------------------------------------------------------------------
      bool operator==(const reverse_iterator &rhs) 
      {
	return (rhs._pos == _pos);
      }

      //----------------------------------------------------------------------------------------------
      bool operator!=(const reverse_iterator &rhs) 
      {
	return !(rhs._pos == _pos);
      }

      //----------------------------------------------------------------------------------------------
      T & operator*()
      {
	return _pDA->_array[_pDA->relative_index(_pos)];
      }

      //----------------------------------------------------------------------------------------------
      const T & operator*() const
      {
	return _pDA->_array[_pDA->relative_index(_pos)];
      }

    };


  public:

    //------------------------------------------------------------------------------------------------
    dynamic_array(size_t n = 0, const T &t = T());

    //------------------------------------------------------------------------------------------------
    ~dynamic_array();

    //------------------------------------------------------------------------------------------------
    dynamic_array(const dynamic_array & rhs);

    //------------------------------------------------------------------------------------------------
    dynamic_array operator=(const dynamic_array & rhs);

    //------------------------------------------------------------------------------------------------
    void push_back(const T &t);

    //------------------------------------------------------------------------------------------------
    void pop_back();

    //------------------------------------------------------------------------------------------------
    void pop_front();

    //------------------------------------------------------------------------------------------------
    size_t   size() const;
    size_t   capacity() const;

    //------------------------------------------------------------------------------------------------
    bool     empty() const;

    //------------------------------------------------------------------------------------------------
    T &       operator[](size_t i);
    const T & operator[](size_t i) const;

    //------------------------------------------------------------------------------------------------
    T &       front();
    const T & front() const;

    //------------------------------------------------------------------------------------------------
    T &       back();
    const T & back() const;

    //------------------------------------------------------------------------------------------------
    iterator begin()
    {
      return typename dynamic_array::iterator(this, _back - _front ? _front : iterator::RightSentinel);
    }

    //------------------------------------------------------------------------------------------------	
    iterator end()
    {
      return typename dynamic_array::iterator(this);
    }

    //------------------------------------------------------------------------------------------------
    reverse_iterator rbegin()
    {
      return typename dynamic_array::reverse_iterator(this, _back - _front ? _back - 1 : iterator::LeftSentinel);
    }

    //------------------------------------------------------------------------------------------------	
    reverse_iterator rend()
    {
      return typename dynamic_array::reverse_iterator(this);
    }
  };


  //--------------------------------------------------------------------------------------------------
  template <typename T>
    const int dynamic_array<T>::iterator::LeftSentinel = -1;
  
  //--------------------------------------------------------------------------------------------------
  template <typename T>
    const int dynamic_array<T>::iterator::RightSentinel = -2;

  //--------------------------------------------------------------------------------------------------
  template <typename T>
    dynamic_array<T>::dynamic_array(size_t n, const T &t) :
    _capacity (next_power_of_2(n)),
    _front    (0),
    _back     (n),
    _array    (new T[_capacity])
    {
      std::fill_n(_array, n, t);
      
      //for(size_t i = 0; i < n; ++i)
      //std::memcpy(_array + i, &t, sizeof(T));
    }

    //--------------------------------------------------------------------------------------------------
    template <typename T>
    dynamic_array<T>::~dynamic_array()
    {
      delete [] _array;
    }

    //Use Copy Semantics
    //--------------------------------------------------------------------------------------------------
    template <typename T>
      dynamic_array<T>::dynamic_array(const dynamic_array & rhs) :
    _capacity (rhs._capacity),
      _front    (rhs._front),
      _back     (rhs._back),
      _array    (new T[_capacity])
	{
	  if(relative_index(_front) < relative_index(_back))
	    {
	      std::memcpy(_array + relative_index(_front), rhs._array + relative_index(_front), (_back - _front) * sizeof(T));
	    }
	  else if(_front != _back)
	    {
	      std::memcpy(_array + relative_index(_front), rhs._array + relative_index(_front), (_capacity - relative_index(_front)) * sizeof(T));
	      std::memcpy(_array, rhs._array, relative_index(_back) * sizeof(T));
	    }
	}

      //--------------------------------------------------------------------------------------------------
      template <typename T>
	dynamic_array<T> dynamic_array<T>::operator=(const dynamic_array & rhs)
	{
	  if(&rhs != this)
	  {
	    _capacity = rhs._capacity;
	      _front    = rhs._front;
	    _back     = rhs._back;			
	    
	    delete [] _array;
	    
	    _array = new T[_capacity];
	    
	    if(relative_index(_front) < relative_index(_back))
	    {
	      std::memcpy(_array + relative_index(_front), rhs._array + relative_index(_front), (_back - _front) * sizeof(T));
            }
	    else if(_front != _back)
	    {
	      std::memcpy(_array + relative_index(_front), rhs._array + relative_index(_front), (_capacity - relative_index(_front)) * sizeof(T));
	      std::memcpy(_array, rhs._array, relative_index(_back) * sizeof(T));
            }
	  }
	  
	  return *this;
	}

      //--------------------------------------------------------------------------------------------------
      template <typename T>
	void dynamic_array<T>::resize(size_t size)
	{
	  T * temp = new T[size];
	  
	  if(relative_index(_front) < relative_index(_back))
	  {
	    std::memcpy(temp, _array + relative_index(_front), (_back - _front) * sizeof(T));
	  }
	  else
	  {
	    std::memcpy(temp, _array + relative_index(_front), (_capacity - relative_index(_front)) * sizeof(T));
	    std::memcpy(temp + (_capacity - relative_index(_front)), _array, relative_index(_back) * sizeof(T));
	  }
	  
	  delete [] _array;

	  _array = temp;
	  
	  //Reset parameters
	  _capacity = size;
	  _back     = _back - _front;
	  _front    = 0;
	}

      //Use Move Semantics
      //--------------------------------------------------------------------------------------------------
      template <>
	dynamic_array<std::string>::dynamic_array(const dynamic_array & rhs) :
        _capacity (rhs._capacity),
	_front    (rhs._front),
	_back     (rhs._back),
	_array    (new std::string[_capacity])
	{
	  if(relative_index(_front) < relative_index(_back))
	  {
	    for(size_t i = 0; i < _back - _front; ++i)
	      _array[relative_index(relative_index(_front)) + i] = std::move(rhs._array[relative_index(_front) + i]);
	  }
	  else
	  {
            for(size_t i = 0; i < (_capacity - relative_index(_front)); ++i)
	      _array[relative_index(_front) + i] = std::move(rhs._array[relative_index(_front) + i]);
	    
            for(size_t i = 0; i < (_capacity - relative_index(_back)); ++i)
	      _array[i] = std::move(rhs._array[relative_index(_back) + i]);
	  }
	}

	//--------------------------------------------------------------------------------------------------
	template <>
	  dynamic_array<std::string> dynamic_array<std::string>::operator=(const dynamic_array & rhs)
	  {
	    if(&rhs != this)
	    {
	      _capacity = rhs._capacity;
	      _front    = rhs._front;
	      _back     = rhs._back;			
	      
	      delete [] _array;
	      
	      _array = new std::string[_capacity];

	      if(relative_index(_front) < relative_index(_back))
	      {
		for(size_t i = 0; i < _back - _front; ++i)
		  _array[relative_index(_front) + i] = std::move(rhs._array[relative_index(_front) + i]);
	      }
	      else
	      {
		for(size_t i = 0; i < (_capacity - relative_index(_front)); ++i)
		  _array[relative_index(_front) + i] = rhs._array[relative_index(_front) + i];
		
		for(size_t i = 0; i < (_capacity - relative_index(_back)); ++i)
		  _array[i] = std::move(rhs._array[relative_index(_back) + i]);
	      }
	    }
		
	    return *this;
	  }

	//--------------------------------------------------------------------------------------------------
	template <>
	  void dynamic_array<std::string>::resize(size_t size)
	  {
	    std::string * temp = new std::string[size];
	    
	    if(relative_index(_front) < relative_index(_back))
	    {
	      for(size_t i = 0; i < _back - _front; ++i)
		temp[i] = std::move(_array[relative_index(_front) + i]);
	    }
	    else
	    {
	      for(size_t i = 0; i < (_capacity - relative_index(_front)); ++i)
		temp[i] = std::move(_array[relative_index(_front) + i]);
	      
	      for(size_t i = 0; i < (_capacity - relative_index(_back)); ++i)
		temp[(_capacity - relative_index(_front)) + i] = std::move(_array[relative_index(_back) + i]);
	    }
	    
	    delete [] _array;
	    
	    _array = temp;
	    
	    //Reset parameters
	    _capacity = size;
	    _back     = _back - _front;
	    _front    = 0;
	  }
	
	//--------------------------------------------------------------------------------------------------
	template <typename T>
	  int dynamic_array<T>::next_power_of_2(int n)
	  {
	    if(n < 2)
	      return n + 1;
	    
	    int i = 2;
	    
	    do
	    {
	      i <<= 1;
	    }while(i <= n);
	    
	    return i;
	  }

	//--------------------------------------------------------------------------------------------------
	template <typename T>
	  int dynamic_array<T>::relative_index(int i)
	  {
	    return i & (_capacity - 1);
	  }
	
	//--------------------------------------------------------------------------------------------------
	template <typename T>
	  void dynamic_array<T>::push_back(const T &t)
	  {
	    //Double the capacity if we loop around and sum to capacity
	    if(_back - _front == _capacity)
	      resize(_capacity << 1);
	    
	    _array[_back++ & (_capacity - 1)] = t;
	  }

	//--------------------------------------------------------------------------------------------------
	template <typename T>
	  void dynamic_array<T>::pop_back()
	  {
	    //Halve the capacity if we utilize less than a fourth
	    if(_back - _front == _capacity >> 2)
	      resize(_capacity >> 1);
	    
	    --_back;
	  }

	//--------------------------------------------------------------------------------------------------
	template <typename T>
	  void dynamic_array<T>::pop_front()
	  {
	    //Halve the capacity if we utilize less than a fourth
	    if(_back - _front == _capacity >> 2)
	      resize(_capacity >> 1);

	    ++_front;
	  }

	//--------------------------------------------------------------------------------------------------
	template <typename T>
	  size_t   dynamic_array<T>::size() const
	  {
	    return (_back - _front);
	  }

	//--------------------------------------------------------------------------------------------------
	template <typename T>
	  size_t   dynamic_array<T>::capacity() const
	  {
	    return _capacity;
	  }

	//--------------------------------------------------------------------------------------------------
	template <typename T>
	  bool   dynamic_array<T>::empty() const
	  {
	    return (_back - _front) == 0;
	  }

	//--------------------------------------------------------------------------------------------------
	template <typename T>
	  T &       dynamic_array<T>::operator[](size_t i)
	  {
	    return _array[relative_index(relative_index(_front) + i)];
	  }

	//--------------------------------------------------------------------------------------------------
	template <typename T>
	  const T & dynamic_array<T>::operator[](size_t i) const
	  {
	    return _array[relative_index(relative_index(_front) + i)];
	  }

	//--------------------------------------------------------------------------------------------------
	template <typename T>
	  T &       dynamic_array<T>::front()
	  {
	    return _array[relative_index(_front)];
	  }

	//--------------------------------------------------------------------------------------------------
	template <typename T>
	  const T & dynamic_array<T>::front() const
	  {
	    return _array[relative_index(_front)];
	  }

	//--------------------------------------------------------------------------------------------------
	template <typename T>
	  T &       dynamic_array<T>::back()
	  {
	    return _array[relative_index(_back - 1)];
	  }

	//--------------------------------------------------------------------------------------------------
	template <typename T>
	  const T & dynamic_array<T>::back() const
	  {
	    return _array[relative_index(_back - 1)];
	  }

}  // close namespace dynamic_array

#endif

