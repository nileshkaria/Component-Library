#include <cstring>
#include <map>
#include <string>
#include <vector>

namespace Serialization 
{
  //==========================================================================================
  class Serializer
  {
  private:
    const char * _pSerialized;
    size_t       _index;

    //----------------------------------------------------------------------------------------
  Serializer(const std::string &rStr) :
    _pSerialized(rStr.c_str()),
      _index(0)
	{}

    //----------------------------------------------------------------------------------------
  Serializer(const char *pStr, size_t size) :
    _pSerialized(pStr),
      _index(0)
	{}
    
    //----------------------------------------------------------------------------------------
    Serializer();
    Serializer(const Serializer&);
    Serializer & operator=(const Serializer&);

    //----------------------------------------------------------------------------------------
    template<typename T>
      bool put(const T &rSource);

    //----------------------------------------------------------------------------------------
    template<typename T>
      bool put(const T* pData, size_t size);

    //----------------------------------------------------------------------------------------
    template <typename T>
      size_t Size(const T& t)
      {
	return sizeof(T);
      }

    //----------------------------------------------------------------------------------------
    template <typename T>
      size_t Size(const T* pt)
      {
	return Size(*pt);
      }

    //----------------------------------------------------------------------------------------
    template <typename T>
      size_t Size(const std::string& t)
      {
	return t.size();
      }

    //----------------------------------------------------------------------------------------
    template <typename T>
      size_t Size(const std::vector<T>& t)
      {
	size_t s(sizeof(size_t));

	for(size_t i = 0; i < t.size(); ++i)
	  s += Size(t[i]);
	
	return s;
      }

    //----------------------------------------------------------------------------------------
    template <typename T>
      size_t Size(const std::vector<T *>& t)
      {
	size_t s(sizeof(size_t));
    
	for(size_t i = 0; i < t.size(); ++i)
	  s += Size(*t[i]);
    
	return s;
      }

    //----------------------------------------------------------------------------------------
    template <typename T, typename U>
      size_t Size(const std::pair<T, U>& p)
    {
      return Size(p.first) + Size(p.second);
    }

    //----------------------------------------------------------------------------------------
    template <typename T, typename U>
      size_t Size(const std::pair<T, U*>& p)
    {
      return Size(p.first) + Size(*p.second);      
    }

    //----------------------------------------------------------------------------------------
    template <typename T, typename U>
      size_t Size(const std::pair<T*, U>& p)
    {
      return Size(*p.first) + Size(p.second);
    }

    //----------------------------------------------------------------------------------------
    template <typename T, typename U>
      size_t Size(const std::pair<T*, U*>& p)
    {
      return Size(*p.first) + Size(*p.second);      
    }

    //----------------------------------------------------------------------------------------
    template <typename T, typename U>
      size_t Size(const std::map<T, U>& m)
    {
      size_t s = 0;

      for(typename std::map<T, U>::const_iterator it = m.begin(); it != m.end; ++it)
	s += Size(*it);

      return s;
    }

    //----------------------------------------------------------------------------------------
    template <typename T, typename U>
      size_t Size(const std::map<T, U *>& m)
    {
      size_t s = 0;

      for(typename std::map<T, U*>::const_iterator it = m.begin(); it != m.end; ++it)
	s += Size(*it);

      return s;
    }

    //----------------------------------------------------------------------------------------
    template <typename T, typename U>
      size_t Size(const std::map<T*, U>& m)
    {
      size_t s = 0;

      for(typename std::map<T*, U>::const_iterator it = m.begin(); it != m.end; ++it)
	s += Size(*it);

      return s;
    }

    //----------------------------------------------------------------------------------------
    template <typename T, typename U>
      size_t Size(const std::map<T*, U*>& m)
    {
      size_t s = 0;

      for(typename std::map<T*, U*>::const_iterator it = m.begin(); it != m.end; ++it)
	s += Size(*it);

      return s;
    }

    //----------------------------------------------------------------------------------------
    friend class SerializerFactory;

  public:
    //----------------------------------------------------------------------------------------
    ~Serializer() {}

    //----------------------------------------------------------------------------------------
    std::string getSerializedData() const
      {
	return _pSerialized ? std::string(_pSerialized, _index) : std::string();
      }

    //----------------------------------------------------------------------------------------
    template <typename T>
      bool Serialize(const T& t)
      {
	return put(t);
      }

    //----------------------------------------------------------------------------------------
    template <typename T>
      bool Serialize(const T* pt, size_t size)
      {
	return put(pt, size);
      }

    //----------------------------------------------------------------------------------------
    template <typename T>
      bool Serialize(const std::vector<T>& t)
      {
	size_t size(t.size());

	if(!Serialize(size))
	  return false;	

	for(size_t i = 0; i < size; ++i)
	  {
	    if(!Serialize(t[i]))
	      return false;
	  }

	return true;
      }

    //----------------------------------------------------------------------------------------
    template <typename T>
      bool Serialize(const std::vector<T *>& t)
      {
	size_t size(t.size());

	if(!Serialize(size))
	  return false;

	for(size_t i = 0; i < size; ++i)
	  {
	    if(!Serialize(*t[i]))
	      return false;
	  }

	return true;
      }

    //----------------------------------------------------------------------------------------
    template <typename T, typename U>
      bool Serialize(const std::pair<T, U>& p)
    {
      return Serialize(p.first) && Serialize(p.second);
    }

    //----------------------------------------------------------------------------------------
    template <typename T, typename U>
      bool Serialize(const std::pair<T, U*>& p)
    {
      return Serialize(p.first) && Serialize(*p.second);      
    }

    //----------------------------------------------------------------------------------------
    template <typename T, typename U>
      bool Serialize(const std::pair<T*, U>& p)
    {
      return Serialize(*p.first) && Serialize(p.second);
    }

    //----------------------------------------------------------------------------------------
    template <typename T, typename U>
      bool Serialize(const std::pair<T*, U*>& p)
    {
      return Serialize(*p.first) && Serialize(*p.second);      
    }

    //----------------------------------------------------------------------------------------
    template <typename T, typename U>
      bool Serialize(const std::pair<const T, U>& p)
    {
      return Serialize(p.first) && Serialize(p.second);
    }

    //----------------------------------------------------------------------------------------
    template <typename T, typename U>
      bool Serialize(const std::pair<const T, U*>& p)
    {
      return Serialize(p.first) && Serialize(*p.second);      
    }

    //----------------------------------------------------------------------------------------
    template <typename T, typename U>
      bool Serialize(const std::pair<const T*, U>& p)
    {
      return Serialize(*p.first) && Serialize(p.second);
    }

    //----------------------------------------------------------------------------------------
    template <typename T, typename U>
      bool Serialize(const std::pair<const T*, U*>& p)
    {
      return Serialize(*p.first) && Serialize(*p.second);      
    }

    //----------------------------------------------------------------------------------------
    template <typename T, typename U>
      bool Serialize(const std::map<T, U>& m)
    {
      size_t size(m.size());

      if(!Serialize(size))
	return false;

      for(typename std::map<T, U>::const_iterator it = m.begin(); it != m.end(); ++it)
	{
	  if(!Serialize(*it))
	    return false;
	}

      return true;
    }

    //----------------------------------------------------------------------------------------
    template <typename T, typename U>
      bool Serialize(const std::map<T, U *>& m)
    {
      size_t size(m.size());

      if(!Serialize(size))
	return false;

      for(typename std::map<T, U*>::const_iterator it = m.begin(); it != m.end(); ++it)
	{
	  if(!Serialize(*it))
	    return false;
	}
      
      return true;
    }

    //----------------------------------------------------------------------------------------
    template <typename T, typename U>
      bool Serialize(const std::map<T*, U>& m)
    {
      size_t size(m.size());

      if(!Serialize(size))
	return false;

      for(typename std::map<T*, U>::const_iterator it = m.begin(); it != m.end(); ++it)
	{
	  if(!Serialize(*it))
	    return false;
	}
      
      return true;
    }

    //----------------------------------------------------------------------------------------
    template <typename T, typename U>
      bool Serialize(const std::map<T*, U*>& m)
    {
      size_t size(m.size());

      if(!Serialize(size))
	return false;

      for(typename std::map<T*, U*>::const_iterator it = m.begin(); it != m.end(); ++it)
	{
	  if(!Serialize(*it))
	    return false;
	}
      
      return true;
    }

  };

  //==========================================================================================
  //Partial specializations for Serializer
  template <>
    inline size_t Serializer::Size<std::string>(const std::string& t)
    {
      return t.size();
    }

  //----------------------------------------------------------------------------------------
  template <>
    bool Serializer::Serialize<std::string>(const std::string& t)
    {
      return put(t.c_str(), t.size());
    }

  //------------------------------------------------------------------------------------------
  template <typename T>
    bool Serializer::put(const T&rData)
    {
      size_t size  = Size(rData);
      size_t usize = sizeof(size_t);
      
      if(!(_pSerialized + _index))
	return false;

      memcpy(const_cast<char *>(_pSerialized) + _index, &size, usize);
    
      //cout << "Writing content " << size << " Size: " << usize << endl;

      _index += usize;

      memcpy(const_cast<char *>(_pSerialized) + _index, &rData, size);

      _index += size;

      //cout << "Writing content " << rData << " Size: " << size << endl;

      return true;
    }

  //------------------------------------------------------------------------------------------
  template <typename T>
    bool Serializer::put(const T* pData, size_t size)
    {
      if(!size || !pData)
	return false;

      size_t usize = sizeof(size_t);
      
      if(!(_pSerialized + _index))
	return false;

      memcpy(const_cast<char *>(_pSerialized) + _index, &size, usize);

      //cout << "Writing content * " << sizeof(size_t) << endl;

      _index += usize;

      memcpy(const_cast<char *>(_pSerialized) + _index, pData, size);

      _index += size;

      return true;
    }

  //==========================================================================================
  class AbstractSerializer
  {
  private:
    //----------------------------------------------------------------------------------------
    virtual bool customizeSerialization(Serializer *pSerializer) = 0;
    
  public:
    //----------------------------------------------------------------------------------------
    AbstractSerializer() {}

    //----------------------------------------------------------------------------------------
    ~AbstractSerializer() {}

    //----------------------------------------------------------------------------------------
    bool serialize(Serializer *pSerializer);
  };

  //----------------------------------------------------------------------------------------
  bool AbstractSerializer::serialize(Serializer *pSerializer)
    {
      return customizeSerialization(pSerializer);    
    }

  //==========================================================================================
  class SerializerFactory
  {
  private:
    static Serializer * _pSerializer;

  public:
    //----------------------------------------------------------------------------------------
    static Serializer * createSerializer(const std::string &rStr)
    {
      if(!_pSerializer)
	_pSerializer = new Serializer(rStr);
      
      return _pSerializer;
    }

    //----------------------------------------------------------------------------------------
    static Serializer * createSerializer(const char *pStr, size_t size)
    {
      if(!_pSerializer)
	_pSerializer = new Serializer(pStr, size);
      
      return _pSerializer;
    }

    //----------------------------------------------------------------------------------------
    static void destroySerializer()
    {
      if(_pSerializer)
	{
	  delete _pSerializer;
	  _pSerializer = 0;
	}
    }
  };

  Serializer * SerializerFactory::_pSerializer = 0;

} // end namespace Serialization 

namespace Deserialization 
{
  //==========================================================================================
  class Deserializer
  {
  private:
    const char * _pDeserialized;
    size_t       _index;
    size_t       _capacity;

    //----------------------------------------------------------------------------------------
  Deserializer(const std::string &rStr) :
    _pDeserialized(rStr.c_str()),
      _index(0),
      _capacity(rStr.length())
	{}

    //----------------------------------------------------------------------------------------
  Deserializer(const char *pStr, size_t size) :
    _pDeserialized(pStr),
      _index(0),
      _capacity(size)
      {}
    
    //----------------------------------------------------------------------------------------
    Deserializer();
    Deserializer(const Deserializer&);
    Deserializer & operator=(const Deserializer&);

    //----------------------------------------------------------------------------------------
    template<typename T>
      bool get(T &rData);

    //----------------------------------------------------------------------------------------
    template<typename T>
      bool get(const T* pData, size_t size);

    //----------------------------------------------------------------------------------------
    friend class DeserializerFactory;

  public:

    //----------------------------------------------------------------------------------------
    ~Deserializer() {}

    //----------------------------------------------------------------------------------------
    template <typename T>
      bool Deserialize(T& t)
      {
	return get(t);
      }

    //----------------------------------------------------------------------------------------
    template <typename T>
      bool Deserialize(const T* pt, size_t size)
      {
	return get(pt, size);
      }

    //----------------------------------------------------------------------------------------
    template <typename T>
      bool Deserialize(std::vector<T>& t)
      {
	size_t size(0);

	if(!Deserialize(size))
	  return false;

	t.resize(size);

	for(size_t i = 0; i < size; ++i)
	  {
	    if(!Deserialize(t[i]))
	      return false;
	  }

	return true;
      }

    //----------------------------------------------------------------------------------------
    template <typename T>
      bool Deserialize(std::vector<T *>& t)
      {
	size_t size(0);

	if(!Deserialize(size))
	  return false;

	t.resize(size);

	for(size_t i = 0; i < size; ++i)
	  {
	    t[i] = new T();

	    if(!Deserialize(*t[i]))
	      return false;
	  }
    
	return true;
      }

    //----------------------------------------------------------------------------------------
    template <typename T, typename U>
      bool Deserialize(std::pair<T, U>& p)
    {
      return Deserialize(p.first) && Deserialize(p.second);
    }

    //----------------------------------------------------------------------------------------
    template <typename T, typename U>
      bool Deserialize(std::pair<T, U*>& p)
    {
      if(!Deserialize(p.first))
	return false;
      
      p.second = new U();
      
      return Deserialize(*p.second);
    }

    //----------------------------------------------------------------------------------------
    template <typename T, typename U>
      bool Deserialize(std::pair<T*, U>& p)
    {
      p.first = new T();

      return Deserialize(*p.first) && Deserialize(p.second);
    }

    //----------------------------------------------------------------------------------------
    template <typename T, typename U>
      bool Deserialize(std::pair<T*, U*>& p)
    {
      p.first = new T();

      if(!Deserialize(*p.first))
	return false;
	  
      p.second = new U();

      return Deserialize(*p.second);
    }

    //----------------------------------------------------------------------------------------
    template <typename T, typename U>
      bool Deserialize(std::map<T, U>& m)
    {
      size_t size(0);

      if(!Deserialize(size))
	return false;

      for(size_t i = 0; i < size; ++i)
	{
	  std::pair<T, U> p;
	  
	  if(!Deserialize(p))
	    return false;

	  m.insert(p);
	}

      return true;
    }

    //----------------------------------------------------------------------------------------
    template <typename T, typename U>
      bool Deserialize(std::map<T, U*>& m)
    {
      size_t size(0);

      if(!Deserialize(size))
	return false;

      for(size_t i = 0; i < size; ++i)
	{
	  std::pair<T, U*> p;
	  
	  if(!Deserialize(p))
	    return false;

	  m.insert(p);
	}

      return true;
    }

    //----------------------------------------------------------------------------------------
    template <typename T, typename U>
      bool Deserialize(std::map<T*, U>& m)
    {
      size_t size(0);

      if(!Deserialize(size))
	return false;

      for(size_t i = 0; i < size; ++i)
	{
	  std::pair<T*, U> p;
	  
	  if(!Deserialize(p))
	    return false;

	  m.insert(p);
	}

      return true;
    }

    //----------------------------------------------------------------------------------------
    template <typename T, typename U>
      bool Deserialize(std::map<T*, U*>& m)
    {
      size_t size(0);

      if(!Deserialize(size))
	return false;

      for(size_t i = 0; i < size; ++i)
	{
	  std::pair<T*, U*> p;
	  
	  if(!Deserialize(p))
	    return false;

	  m.insert(p);
	}

      return true;
    }
  };

  //------------------------------------------------------------------------------------------
  template <typename T>
    bool Deserializer::get(T& rData)
    {
      size_t usize(sizeof(size_t));

      //cout << "index " << _index << " usize " << usize << " capacity " << _capacity << endl;

      if(!_pDeserialized || (_index + usize) > _capacity)
	return false;

      size_t size;

      //cout << "Reading content " << endl;

      memcpy(reinterpret_cast<void *>(&size), _pDeserialized + _index, usize);
  
      _index += usize;

      if(!(_pDeserialized + _index) || _index + size > _capacity)
	return false;

      //cout << "Reading bytes " << size << endl;

      memcpy(const_cast<T *>(&rData), _pDeserialized + _index, size);

      _index += size;

      return true;
    } 
  
  //==========================================================================================
  //Partial specializations for Deserializer
  template <typename T>
    bool Deserializer::get(const T* pData, size_t size)
    {
      if(!(_pDeserialized + _index) || _index + size > _capacity)
	return false;

      memcpy(const_cast<T *>(pData), _pDeserialized + _index, size);

      _index += size;

      return true;
    }  

  //----------------------------------------------------------------------------------------
  template <>
    bool Deserializer::Deserialize<std::string>(std::string& t)
    {
      size_t usize(sizeof(size_t));
    
      //cout << "index " << _index << " usize " << usize << " capacity " << _capacity << endl;
    
      if(!_pDeserialized || (_index + usize) > _capacity)
	return false;
    
      size_t size;
    
      //cout << "Reading content string " << endl;
    
      memcpy(reinterpret_cast<void *>(&size), _pDeserialized + _index, usize);
    
      _index += usize;
      
      if(!(_pDeserialized + _index) || _index + size > _capacity)
	return false;
    
      t.resize(size);
    
      return get(t.c_str(), size);
    }

  //==========================================================================================
  class AbstractDeserializer
  {
  private:
    //----------------------------------------------------------------------------------------
    virtual bool customizeDeserialization(Deserializer *pDeserializer) = 0;
    
  public:
    //----------------------------------------------------------------------------------------
    AbstractDeserializer() {}

    //----------------------------------------------------------------------------------------
    ~AbstractDeserializer() {}

    //----------------------------------------------------------------------------------------
    bool deserialize(Deserializer *pDeserializer);
  };

  //----------------------------------------------------------------------------------------
  bool AbstractDeserializer::deserialize(Deserializer *pDeserializer)
    {
      return customizeDeserialization(pDeserializer);
    }

  //==========================================================================================
  class DeserializerFactory
  {
  private:
    static Deserializer * _pDeserializer;

  public:
    //----------------------------------------------------------------------------------------
    static Deserializer * createDeserializer(const char *pStr, size_t size)
    {
      if(!_pDeserializer)
	_pDeserializer = new Deserializer(pStr, size);
      
      return _pDeserializer; 
    }

    //----------------------------------------------------------------------------------------
    static Deserializer * createDeserializer(const std::string &rStr)
    {
      if(!_pDeserializer)
	_pDeserializer = new Deserializer(rStr);
      
      return _pDeserializer;
    }

    //----------------------------------------------------------------------------------------
    static void destroyDeserializer()
    {
      if(_pDeserializer)
	{
	  delete _pDeserializer;
	  _pDeserializer = 0;
	}
    }
  };

  Deserializer * DeserializerFactory::_pDeserializer = 0;

} // end namespace Deserialization 
