
// C++ includes
#include <iostream>
#include <forward_list> // C++11 newly added list
// Boost includes
#include <boost/assign/list_of.hpp>
#include <boost/assign/std/vector.hpp>

namespace cpp11 
{
  // Singly linked list to be traversed in only one direction
  void testForwardList()
  {
    using namespace std;
    using namespace boost::assign;
    
    std::cout << "We are testing the forward list newly added to c++11\n"; 

    // create a forward list
    std::forward_list<int> w_testFwdList;
    w_testFwdList = list_of(1)(2)(3)(4)(5);
    for( const auto& val : w_testFwdList)
    {
      std::cout << "Element of the forward list are: " << val << " ";
    }
  }
} // End of namespace