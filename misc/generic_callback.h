#ifndef __GENERIC_CALLBACK_H_GUARD_
#define __GENERIC_CALLBACK_H_GUARD_

#include <typeinfo>
//#include <atomic>

//============================================================================================
/*
  This templatized callback class provides the ability to create containers of different types 
  of callbacks taking in one parameter. Specifically, non-const, const and global pointers to
  function can be added to a container of type GenericCallback::AbstractCallbackContainer.

  This class provides the flexibility in storing callbacks taking in one argument while being 
  of different constness or scope and running these asynchronously in batch at a later time.
  The parameter passed in is stored in the callback object to be used later. The three classes
  below - genericCallback, genericConstCallback and genericGlobalCallback are extended to 
  take in upto six parameters at initiation. This allows mixing different kinds of callbacks 
  taking in a disparate type and number of arguments. 

  These callback are reference counted and deleted upon execution. This can be made threadsafe 
  using C++11's atomic<int> for AbstractCallbackContainer::flag.

  Since only one type of pointer to function is needed for each generic callback, the method
  parameter is stored in a union to conserve memory allocated. However, note that each container 
  contains at most five unused parameters which have a default allocation of one 'unit' adding
  one byte per unused parameter object.
*/
//============================================================================================

namespace GenericCallback
{
  //==========================================================================================
  //Use an empty struct with resultant bytesize 1 to pass as void default template param type
  struct unit {};

  //==========================================================================================
  template<class C, 
    typename T, 
    typename P1, 
    typename P2 = unit,
    typename P3 = unit,
    typename P4 = unit,
    typename P5 = unit,
    typename P6 = unit>
    class genericCallback
    {
    public:
    //----------------------------------------------------------------------------------------
    typedef T(C::*CallbackMethod1)(P1);
    typedef T(C::*CallbackMethod2)(P1, P2);
    typedef T(C::*CallbackMethod3)(P1, P2, P3);
    typedef T(C::*CallbackMethod4)(P1, P2, P3, P4);
    typedef T(C::*CallbackMethod5)(P1, P2, P3, P4, P5);
    typedef T(C::*CallbackMethod6)(P1, P2, P3, P4, P5, P6);
  
    private:
    //----------------------------------------------------------------------------------------  
    C                  *_pClass;

    union
    {
      CallbackMethod1   _method1;
      CallbackMethod2   _method2;
      CallbackMethod3   _method3;
      CallbackMethod4   _method4;
      CallbackMethod5   _method5;
      CallbackMethod6   _method6;
    };

    public:
    //----------------------------------------------------------------------------------------  
    genericCallback(C * pClass, CallbackMethod1 method1) :
    _pClass  (pClass),
    _method1 (method1)
    {}

    //----------------------------------------------------------------------------------------  
    genericCallback(C * pClass, CallbackMethod2 method2) :
    _pClass  (pClass),
    _method2 (method2)
    {}

    //----------------------------------------------------------------------------------------  
    genericCallback(C * pClass, CallbackMethod3 method3) :
    _pClass  (pClass),
    _method3 (method3)
    {}

    //----------------------------------------------------------------------------------------  
    genericCallback(C * pClass, CallbackMethod4 method4) :
    _pClass  (pClass),
    _method4 (method4)
    {}

    //----------------------------------------------------------------------------------------  
    genericCallback(C * pClass, CallbackMethod5 method5) :
    _pClass  (pClass),
    _method5 (method5)
    {}

    //----------------------------------------------------------------------------------------  
    genericCallback(C * pClass, CallbackMethod6 method6) :
    _pClass  (pClass),
    _method6 (method6)
    {}

    //----------------------------------------------------------------------------------------
    T operator()(P1 param1)
    {
      return (_pClass->*_method1)(param1);
    }

    //----------------------------------------------------------------------------------------
    T operator()(P1 param1, P2 param2)
    {
      return (_pClass->*_method2)(param1, param2);
    }

    //----------------------------------------------------------------------------------------
    T operator()(P1 param1, P2 param2, P3 param3)
    {
      return (_pClass->*_method3)(param1, param2, param3);
    }

    //----------------------------------------------------------------------------------------
    T operator()(P1 param1, P2 param2, P3 param3, P4 param4)
    {
      return (_pClass->*_method4)(param1, param2, param3, param4);
    }

    //----------------------------------------------------------------------------------------
    T operator()(P1 param1, P2 param2, P3 param3, P4 param4, P5 param5)
    {
      return (_pClass->*_method5)(param1, param2, param3, param4, param5);
    }

    //----------------------------------------------------------------------------------------
    T operator()(P1 param1, P2 param2, P3 param3, P4 param4, P5 param5, P6 param6)
    {
      return (_pClass->*_method6)(param1, param2, param3, param4, param5, param6);
    }

    };

  //==========================================================================================
  template<class    C, 
    typename T, 
    typename P1, 
    typename P2 = unit,
    typename P3 = unit,
    typename P4 = unit,
    typename P5 = unit,
    typename P6 = unit>
    class genericConstCallback
    {
    public:
    //----------------------------------------------------------------------------------------
    typedef T(C::*ConstCallbackMethod1)(P1) const;
    typedef T(C::*ConstCallbackMethod2)(P1, P2) const;
    typedef T(C::*ConstCallbackMethod3)(P1, P2, P3) const;
    typedef T(C::*ConstCallbackMethod4)(P1, P2, P3, P4) const;
    typedef T(C::*ConstCallbackMethod5)(P1, P2, P3, P4, P5) const;
    typedef T(C::*ConstCallbackMethod6)(P1, P2, P3, P4, P5, P6) const;
  
    private:
    //----------------------------------------------------------------------------------------  
    C                    *_pClass;

    union
    {
      ConstCallbackMethod1   _method1;
      ConstCallbackMethod2   _method2;
      ConstCallbackMethod3   _method3;
      ConstCallbackMethod4   _method4;
      ConstCallbackMethod5   _method5;
      ConstCallbackMethod6   _method6;
    };

    public:

    //----------------------------------------------------------------------------------------  
    genericConstCallback(C * pClass, ConstCallbackMethod1 method1) :
    _pClass  (pClass),
    _method1 (method1)
    {}

    //----------------------------------------------------------------------------------------  
    genericConstCallback(C * pClass, ConstCallbackMethod2 method2) :
    _pClass  (pClass),
    _method2 (method2)
    {}

    //----------------------------------------------------------------------------------------  
    genericConstCallback(C * pClass, ConstCallbackMethod3 method3) :
    _pClass  (pClass),
    _method3 (method3)
    {}

    //----------------------------------------------------------------------------------------  
    genericConstCallback(C * pClass, ConstCallbackMethod4 method4) :
    _pClass  (pClass),
    _method4 (method4)
    {}

    //----------------------------------------------------------------------------------------  
    genericConstCallback(C * pClass, ConstCallbackMethod5 method5) :
    _pClass  (pClass),
    _method5 (method5)
    {}

    //----------------------------------------------------------------------------------------  
    genericConstCallback(C * pClass, ConstCallbackMethod6 method6) :
    _pClass  (pClass),
    _method6 (method6)
    {}

    //----------------------------------------------------------------------------------------
    T operator()(P1 param1)
    {
      return (_pClass->*_method1)(param1);
    }

    //----------------------------------------------------------------------------------------
    T operator()(P1 param1, P2 param2)
    {
      return (_pClass->*_method2)(param1, param2);
    }

    //----------------------------------------------------------------------------------------
    T operator()(P1 param1, P2 param2, P3 param3)
    {
      return (_pClass->*_method3)(param1, param2, param3);
    }

    //----------------------------------------------------------------------------------------
    T operator()(P1 param1, P2 param2, P3 param3, P4 param4)
    {
      return (_pClass->*_method4)(param1, param2, param3, param4);
    }

    //----------------------------------------------------------------------------------------
    T operator()(P1 param1, P2 param2, P3 param3, P4 param4, P5 param5)
    {
      return (_pClass->*_method5)(param1, param2, param3, param4, param5);
    }

    //----------------------------------------------------------------------------------------
    T operator()(P1 param1, P2 param2, P3 param3, P4 param4, P5 param5, P6 param6)
    {
      return (_pClass->*_method6)(param1, param2, param3, param4, param5, param6);
    }

    };

  //==========================================================================================
  template<typename T, 
    typename P1, 
    typename P2 = unit,
    typename P3 = unit,
    typename P4 = unit,
    typename P5 = unit,
    typename P6 = unit>
    class genericGlobalCallback
    {
    public:
    //----------------------------------------------------------------------------------------
    typedef T(*GlobalCallbackMethod1)(P1);
    typedef T(*GlobalCallbackMethod2)(P1, P2);
    typedef T(*GlobalCallbackMethod3)(P1, P2, P3);
    typedef T(*GlobalCallbackMethod4)(P1, P2, P3, P4);
    typedef T(*GlobalCallbackMethod5)(P1, P2, P3, P4, P5);
    typedef T(*GlobalCallbackMethod6)(P1, P2, P3, P4, P5, P6);
  
    private:
    //----------------------------------------------------------------------------------------  
    union
    {
      GlobalCallbackMethod1   _method1;
      GlobalCallbackMethod2   _method2;
      GlobalCallbackMethod3   _method3;
      GlobalCallbackMethod4   _method4;
      GlobalCallbackMethod5   _method5;
      GlobalCallbackMethod6   _method6;
    };

    public:
    //----------------------------------------------------------------------------------------  
    genericGlobalCallback(const GlobalCallbackMethod1 method1) :
    _method1 (method1)
    {}

    //----------------------------------------------------------------------------------------  
    genericGlobalCallback(const GlobalCallbackMethod2 method2) :
    _method2 (method2)
    {}

    //----------------------------------------------------------------------------------------  
    genericGlobalCallback(const GlobalCallbackMethod3 method3) :
    _method3 (method3)
    {}

    //----------------------------------------------------------------------------------------  
    genericGlobalCallback(const GlobalCallbackMethod4 method4) :
    _method4 (method4)
    {}

    //----------------------------------------------------------------------------------------  
    genericGlobalCallback(const GlobalCallbackMethod5 method5) :
    _method5 (method5)
    {}

    //----------------------------------------------------------------------------------------  
    genericGlobalCallback(const GlobalCallbackMethod6 method6) :
    _method6 (method6)
    {}

    //----------------------------------------------------------------------------------------
    T operator()(P1 param1)
    {
      return (*_method1)(param1);
    }

    //----------------------------------------------------------------------------------------
    T operator()(P1 param1, P2 param2)
    {
      return (*_method2)(param1, param2);
    }

    //----------------------------------------------------------------------------------------
    T operator()(P1 param1, P2 param2, P3 param3)
    {
      return (*_method3)(param1, param2, param3);
    }

    //----------------------------------------------------------------------------------------
    T operator()(P1 param1, P2 param2, P3 param3, P4 param4)
    {
      return (*_method4)(param1, param2, param3, param4);
    }

    //----------------------------------------------------------------------------------------
    T operator()(P1 param1, P2 param2, P3 param3, P4 param4, P5 param5)
    {
      return (*_method5)(param1, param2, param3, param4, param5);
    }

    //----------------------------------------------------------------------------------------
    T operator()(P1 param1, P2 param2, P3 param3, P4 param4, P5 param5, P6 param6)
    {
      return (*_method6)(param1, param2, param3, param4, param5, param6);
    }

    };

  //==========================================================================================
  class AbstractCallbackContainer
  {
  private:
    //----------------------------------------------------------------------------------------  
    int   flag;

  public:
    //----------------------------------------------------------------------------------------
  AbstractCallbackContainer() : 
    flag(1)
      {}

    //----------------------------------------------------------------------------------------
    virtual void operator()() = 0;

    //----------------------------------------------------------------------------------------
    int addref()
    {
      return ++flag;
    }
    
    //----------------------------------------------------------------------------------------
    int release()
    {
      int n(--flag);
    
      if(n == 0)
	delete this;
    
      return n;
    }
    
  protected:
    //----------------------------------------------------------------------------------------
    virtual ~AbstractCallbackContainer() = 0;
  };

  //----------------------------------------------------------------------------------------
  AbstractCallbackContainer::~AbstractCallbackContainer() {}

  //==========================================================================================
  template <class C, 
    typename M,
    typename T, 
    typename P1, 
    typename P2 = unit,
    typename P3 = unit,
    typename P4 = unit,
    typename P5 = unit,
    typename P6 = unit>
    class CallbackContainer: public AbstractCallbackContainer
  {
  public:
  //----------------------------------------------------------------------------------------
  typedef T(C::*CallbackMethod1)(P1);
  typedef T(C::*CallbackMethod2)(P1, P2);
  typedef T(C::*CallbackMethod3)(P1, P2, P3);
  typedef T(C::*CallbackMethod4)(P1, P2, P3, P4);
  typedef T(C::*CallbackMethod5)(P1, P2, P3, P4, P5);
  typedef T(C::*CallbackMethod6)(P1, P2, P3, P4, P5, P6);

  private:
  //----------------------------------------------------------------------------------------  
  genericCallback<C, T, P1, P2, P3, P4, P5, P6>  *_pCallback;
  P1                                              _param1;
  P2                                              _param2;
  P3                                              _param3;
  P4                                              _param4;
  P5                                              _param5;
  P6                                              _param6;
    
  public:
  //----------------------------------------------------------------------------------------
  CallbackContainer(C* pClass, 
		    M  method, 
		    P1 param1, 
		    P2 param2 = unit(),
		    P3 param3 = unit(),
		    P4 param4 = unit(),
		    P5 param5 = unit(),
		    P6 param6 = unit()) :
  _pCallback (new genericCallback<C, T, P1, P2, P3, P4, P5, P6>(pClass, method)),
  _param1     (param1),
  _param2     (param2),
  _param3     (param3),
  _param4     (param4),
  _param5     (param5),
  _param6     (param6)
  {}

  //----------------------------------------------------------------------------------------
  virtual ~CallbackContainer()
  {
    delete _pCallback;
  }

  //----------------------------------------------------------------------------------------
  virtual void operator()()
  {
    if(typeid(_param6) != typeid(unit))
      (*_pCallback)(_param1, _param2, _param3, _param4, _param5, _param6);
    else if(typeid(_param5) != typeid(unit))
      (*_pCallback)(_param1, _param2, _param3, _param4, _param5);
    else if(typeid(_param4) != typeid(unit))
      (*_pCallback)(_param1, _param2, _param3, _param4);
    else if(typeid(_param3) != typeid(unit))
      (*_pCallback)(_param1, _param2, _param3);
    else if(typeid(_param2) != typeid(unit))
      (*_pCallback)(_param1, _param2);
    else
      (*_pCallback)(_param1);

    release();
  }

  };

  //==========================================================================================
  template <class C, 
    typename M,
    typename T, 
    typename P1, 
    typename P2 = unit,
    typename P3 = unit,
    typename P4 = unit,
    typename P5 = unit,
    typename P6 = unit>
    class ConstCallbackContainer: public AbstractCallbackContainer
  {
  public:
  //----------------------------------------------------------------------------------------
  typedef T(C::*ConstCallbackMethod1)(P1) const;
  typedef T(C::*ConstCallbackMethod2)(P1, P2) const;
  typedef T(C::*ConstCallbackMethod3)(P1, P2, P3) const;
  typedef T(C::*ConstCallbackMethod4)(P1, P2, P3, P4) const;
  typedef T(C::*ConstCallbackMethod5)(P1, P2, P3, P4, P5) const;
  typedef T(C::*ConstCallbackMethod6)(P1, P2, P3, P4, P5, P6) const;

  private:
  //----------------------------------------------------------------------------------------  
  genericConstCallback<C, T, P1, P2, P3, P4, P5, P6>  *_pCallback;
  P1                                                   _param1;
  P2                                                   _param2;
  P3                                                   _param3;
  P4                                                   _param4;
  P5                                                   _param5;
  P6                                                   _param6;

  public:
  //----------------------------------------------------------------------------------------
  ConstCallbackContainer(C* pClass, 
			 M  method, 
			 P1 param1, 
			 P2 param2 = unit(),
			 P3 param3 = unit(),
			 P4 param4 = unit(),
			 P5 param5 = unit(),
			 P6 param6 = unit()) :
  _pCallback (new genericConstCallback<C, T, P1, P2, P3, P4, P5, P6>(pClass, method)),
  _param1     (param1),
  _param2     (param2),
  _param3     (param3),
  _param4     (param4),
  _param5     (param5),
  _param6     (param6)
  {}

  //----------------------------------------------------------------------------------------
  virtual ~ConstCallbackContainer()
  {
    delete _pCallback;
  }

  //----------------------------------------------------------------------------------------
  virtual void operator()()
  {
    if(typeid(_param6) != typeid(unit))
      (*_pCallback)(_param1, _param2, _param3, _param4, _param5, _param6);
    else if(typeid(_param5) != typeid(unit))
      (*_pCallback)(_param1, _param2, _param3, _param4, _param5);
    else if(typeid(_param4) != typeid(unit))
      (*_pCallback)(_param1, _param2, _param3, _param4);
    else if(typeid(_param3) != typeid(unit))
      (*_pCallback)(_param1, _param2, _param3);
    else if(typeid(_param2) != typeid(unit))
      (*_pCallback)(_param1, _param2);
    else
      (*_pCallback)(_param1);

    release();
  }

  };

  //==========================================================================================
  template <typename M,
    typename T, 
    typename P1, 
    typename P2 = unit,
    typename P3 = unit,
    typename P4 = unit,
    typename P5 = unit,
    typename P6 = unit>
    class GlobalCallbackContainer: public AbstractCallbackContainer
  {
  private:
  //----------------------------------------------------------------------------------------  
  genericGlobalCallback<T, P1, P2, P3, P4, P5, P6>  *_pCallback;
  P1                                                 _param1;
  P2                                                 _param2;
  P3                                                 _param3;
  P4                                                 _param4;
  P5                                                 _param5;
  P6                                                 _param6;

  public:
  //----------------------------------------------------------------------------------------
  typedef T(*GlobalCallbackMethod1)(P1);
  typedef T(*GlobalCallbackMethod2)(P1, P2);
  typedef T(*GlobalCallbackMethod3)(P1, P2, P3);
  typedef T(*GlobalCallbackMethod4)(P1, P2, P3, P4);
  typedef T(*GlobalCallbackMethod5)(P1, P2, P3, P4, P5);
  typedef T(*GlobalCallbackMethod6)(P1, P2, P3, P4, P5, P6);

  //----------------------------------------------------------------------------------------
  GlobalCallbackContainer(M  method, 
			  P1 param1, 
			  P2 param2 = unit(),
			  P3 param3 = unit(),
			  P4 param4 = unit(),
			  P5 param5 = unit(),
			  P6 param6 = unit()) :
  _pCallback (new genericGlobalCallback<T, P1, P2, P3, P4, P5, P6>(method)),
  _param1     (param1),
  _param2     (param2),
  _param3     (param3),
  _param4     (param4),
  _param5     (param5),
  _param6     (param6)
  {}

  //----------------------------------------------------------------------------------------
  virtual ~GlobalCallbackContainer()
  {
    delete _pCallback;
  }

  //----------------------------------------------------------------------------------------
  virtual void operator()()
  {
    if(typeid(_param6) != typeid(unit))
      (*_pCallback)(_param1, _param2, _param3, _param4, _param5, _param6);
    else if(typeid(_param5) != typeid(unit))
      (*_pCallback)(_param1, _param2, _param3, _param4, _param5);
    else if(typeid(_param4) != typeid(unit))
      (*_pCallback)(_param1, _param2, _param3, _param4);
    else if(typeid(_param3) != typeid(unit))
      (*_pCallback)(_param1, _param2, _param3);
    else if(typeid(_param2) != typeid(unit))
      (*_pCallback)(_param1, _param2);
    else
      (*_pCallback)(_param1);

    release();
  }
  };

} //end namespace GenericCallback

#endif //end __GENERIC_CALLBACK_H_GUARD_
