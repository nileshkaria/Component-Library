#include <vector>

namespace KMP
{

  //==========================================================================================
  class KMPStringMatcher
  {
  public:
    //----------------------------------------------------------------------------------------
    KMPStringMatcher();

    //----------------------------------------------------------------------------------------
    ~KMPStringMatcher();

    //----------------------------------------------------------------------------------------
    static void findMatches(const std::string &t,
			    const std::string &p,
			    std::vector<int>  &rShift);
  private:
    //----------------------------------------------------------------------------------------
    static void computePrefixFunction(const std::string &p, 
				      std::vector<int>  &PI);
  };

} // end namespace KMPStringMatcher
