#include "serializer.h"

#include <iostream>

using namespace std;
using namespace Serialization;
using namespace Deserialization; 

int main()
{
  string *pSerializedStr = new string();

  Serializer *pS = SerializerFactory::createSerializer(*pSerializedStr);

  double x = 3.14159;
  if(!pS->Serialize(x))
     cout << "Error in serialization at " << __LINE__ << endl;

  string y("The only limit to your imagination is yourself.");
  if(!pS->Serialize(y))
     cout << "Error in serialization at " << __LINE__ << endl;  

  vector<string> v1;
  v1.push_back("111");
  v1.push_back("222");
  if(!pS->Serialize(v1))
     cout << "Error in serialization at " << __LINE__ << endl;

  vector<string *> v2;
  v2.push_back(new string("5678"));
  v2.push_back(new string("9876"));
  if(!pS->Serialize(v2))
     cout << "Error in serialization at " << __LINE__ << endl;

  map<int, string> m1;
  m1[1] = "un";
  m1[2] = "deux";
  m1[3] = "trois";
  if(!pS->Serialize(m1))
     cout << "Error in serialization at " << __LINE__ << endl;

  map<int, vector<string> > m2;
  m2[4] = v1;
  if(!pS->Serialize(m2))
     cout << "Error in serialization at " << __LINE__ << endl;
  //----------------------------------------------------------------------------------------

  string deserialized = pS->getSerializedData();
  if(deserialized.empty())
    cout << "ERROR!" << endl;

  Deserializer *pD = DeserializerFactory::createDeserializer(deserialized);

  double a;
  if(!pD->Deserialize(a))
    cout << "Error in deserialization at " << __LINE__ << endl;
  cout << "a " << a << endl; 

  string b;
  if(!pD->Deserialize(b))
    cout << "Error in deserialization at " << __LINE__ << endl;
  cout << "b " << b << endl;

  vector<string> v3;
  if(!pD->Deserialize(v3))
    cout << "Error in deserialization at " << __LINE__ << endl;

  for(size_t i = 0; i < v3.size(); ++i)
    cout << "v3[" << i << "] " << v3[i] << endl;

  vector<string *> v4;
  if(!pD->Deserialize(v4))
    cout << "Error in deserialization at " << __LINE__ << endl;

  for(size_t i = 0; i < v4.size(); ++i)
    cout << "v4[" << i << "] " << *v4[i] << endl;

  map<int, string> m3;
  if(!pD->Deserialize(m3))
    cout << "Error in deserialization at " << __LINE__ << endl;

  for(map<int, string>::const_iterator it = m3.begin(); it != m3.end(); ++it)
    cout << "m3[" << it->first << "] = " << it->second << endl; 

  map<int, vector<string> > m4;
  if(!pD->Deserialize(m4))
    cout << "Error in deserialization at " << __LINE__ << endl;

  for(map<int, vector<string> >::const_iterator it = m4.begin(); it != m4.end(); ++it)
    {
      cout << "m4[" << it->first << "] : " << endl;
      
      for(size_t i = 0; i < it->second.size(); ++i)
	{
	  cout << "[" << i << "] = " <<  it->second[i] << endl;  
	}
    }
	
  SerializerFactory::destroySerializer();
  DeserializerFactory::destroyDeserializer();
 }
