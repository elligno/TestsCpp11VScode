
// C++11 includes
#include <iostream>
#include <string>
#include <tuple>

namespace cpp11 
{
  // testing tuple of cpp11
  void testTupleCpp11()
  {
    using  tuple_t = std::tuple<double,unsigned,std::string>;
    tuple_t w_tupleCpp = std::make_tuple(2.,1,std::string("tuple"));
    std::cout << "we are testing tuple\n"; 

		// Can we copy tuple? why not!
    // what about stuctured binding C++17? is it working?

		//std::cout << "This is our new created tuple: " << w_tupleCpp << "\n"; 
  }
} // End of namespace