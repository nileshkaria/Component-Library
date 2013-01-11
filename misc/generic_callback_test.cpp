#include <iostream>
#include <vector>

#include "generic_callback.h"

using namespace std;
using namespace GenericCallback;

class Initiator
{
private:
  vector<AbstractCallbackContainer *> v;

public:

  Initiator() : v() {}

  ~Initiator() {}

  typedef void (Initiator::*CM1)(size_t); 
  typedef void (Initiator::*CM2)(size_t, bool); 
  typedef void (Initiator::*CM3)(char);
  typedef void (Initiator::*CCM1)(double) const; 

  void addCallback(int x) 
  {
    cout << "Adding : " << endl;
    cout << " callback [" << x << "]" << endl;

    v.push_back(new CallbackContainer<Initiator, CM1, void, size_t>(this, &Initiator::processCallback, x));

    cout << "Adding : " << endl;
    cout << " callback [" << x << " | " << (x & 0x1) << "]" << endl;

    v.push_back(new CallbackContainer<Initiator, CM2, void, size_t, bool>(this, &Initiator::processCallback, x, (x & 0x1)));

    cout << " const callback [" << x/2.0 << "]" << endl;

    v.push_back(new ConstCallbackContainer<Initiator, CCM1, void, double>(this, &Initiator::processConstCallback, x/2.0));

    cout << " callback [" << static_cast<char>(x + 65) << "]" << endl;

    v.push_back(new CallbackContainer<Initiator, CM3, void, char>(this, &Initiator::processCallback, static_cast<char>(x + 65)));
  }

  void processCallback(size_t index)
  {
    cout << "Processsing callback [" << index << "]" << endl;
  }

  void processCallback(size_t index, bool flip)
  {
    cout << "Processsing callback [" << index << " | " << flip << " ]" << endl;
  }

  void processConstCallback(double d) const
  {
    cout << "Processsing const callback [" << d << "]" << endl;
  }

  void processCallback(char c)
  {
    cout << "Processsing callback [" << c << "]" << endl;
  }

  const vector<AbstractCallbackContainer *> & getCallbacks()
  {
    return v;
  }

};

class Responder
{
public:

  Responder() {}

  ~Responder() {}

  void initiateCallback(const vector<AbstractCallbackContainer *> &rCallbackVec)
  {
    for(size_t i = 0; i < rCallbackVec.size(); ++i)
      (*rCallbackVec[i])();
  }
};

int main()
{
  Initiator * pi = new Initiator();

  for(size_t i = 0; i < 10; ++i)
    pi->addCallback(i);

  cout << "-----------------------------------------------" << endl;

  Responder * pr = new Responder();

  pr->initiateCallback(pi->getCallbacks());

  delete pr;
  delete pi;

  return 0;
}
