
// C++ includes
#include <map>
#include <string>
#include <iostream>
// STL include
#include <vector>
// Boost includes
#include <boost/assert.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
// boost includes
#include <boost/lambda/bind.hpp>  
#include <boost/filesystem.hpp>      // boost file system utility
#include <boost/foreach.hpp>   
// Boost string algorithm
// #include <boost/algorithm/string.hpp>
// #include <boost/algorithm/string/case_conv.hpp>
// #include <boost/algorithm/string/split.hpp>
// #include <boost/algorithm/string/trim_all.hpp>
// boost range includes
// #include <boost/range/adaptors.hpp>            // ...
// #include <boost/range/adaptor/map.hpp>
// #include <boost/range/adaptor/filtered.hpp>    // ...

namespace vs15 
{
	// testing boost install on the vs15 
	void testBoost160()
	{
		using namespace boost;

		// C++ 11 container initialization
		std::vector<std::string> w_vecofstr = {"Jean", "negrito", "toutou"};
		
		// printing result
		std::for_each( std::begin(w_vecofstr), std::end(w_vecofstr),
			[] ( const std::string& aStr2Print) // lambda function
		{
			std::cout << "String is:" << aStr2Print << "\n";
		});
	}

	// list initializer for map, is it possible?
	// key map adapter which is very nice feature of boost library
	void testMapAdaptor()
	{
		std::map<unsigned, std::string> w_testMap;
	}
} // End of namespace