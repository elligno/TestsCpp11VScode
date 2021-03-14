
// C++ includes
#include <iostream>
#include <string>
// stl include
#include <map>
#include <unordered_map>
// Boost includes
#include <boost/range/adaptor/map.hpp>
#include <boost/range/algorithm/copy.hpp>
// package includes
//#include "../Classes/SomeClass.h"
//#include "FFAlgorithm.h"
//#include "../Classes/AlgorithmClass.h"

//namespace aa { void* getCOMPtr( aa::BaseClass* aBaseptr);}

namespace aa 
{
#if 0
	// this will be used in our programming environment
	// in the main function or controller 
	void testFactoryMethods()
	{
		// Some usage of our factory methods design pattern
		Class* w_algoCls = Class::forName( std::string("DBvalidate"));
		
		// in the current version, newInstance return new AlgorithmClass
		// i must delete the pointer here since the factory methods
		// don't do it (actually it return FFAlgorithm which inherit of IConservative)
		// Factory Design Pattern let subclass create instance of object  
		IConservative* w_ffAlgo = (IConservative*)w_algoCls->newInstance();
		
		// sanity check
		if( w_ffAlgo != nullptr)
		{
			// compute flux at the cell interface
			w_ffAlgo->calculFF();
		}

		std::cout << "we are leaving the test factory methods function\n";

		// cast base pointer to derived
		const std::string w_testIterStr("Rabbit");
		std::string w_nonConstStr("TouTou");

		// create a pointer to base class from inherited class
		// this pointer contains information from inherited class
		aa::BaseClass* w_ptr2Base = new aa::inheritSomeClass( w_nonConstStr);
		if( w_ptr2Base == nullptr) // check for null pointer
		{
			std::cout << "Could not create base pointer\n";
		}

		// do some clean-up, for example delete IConservative pointer
	}
#endif
	// testing some basic map functionalities
	void testMap()
	{
		using namespace std;
		using namespace boost::adaptors;

		typedef std::map<std::string,int> map_strint;
		
		// key compare (mean that string need to be comparable)
		std::map<std::string,int> mymap;
       
		string w_str1("jean");
		string w_str2("neaj");
		if( w_str1<w_str2)
		{
			cout << "String1 less than string2\n";
		}

		// first insert function version (single parameter):
		mymap.insert ( std::pair<std::string,int>("asaaa",100) );
		mymap.insert ( std::pair<std::string,int>("zqwqw",100) );
		// check size 
		map_strint::size_type w_sizeMap=mymap.size();

		// now print 
// 		std::map<int,int> input;
// 		for (int i = 0; i < 10; ++i)
// 			input.insert( std::make_pair(i, i * 10));
		
		boost::copy(
			mymap | map_values,
				std::ostream_iterator<int>(std::cout, ","));

		// testing our factory methods that we are implementing 
	//	testFactoryMethods();
	}

  // just testing the multimap
  void testMultiMap()
  {
    // Faire un test avec un double pointer (Interface**)
    // comme chez tech2020 afin de l'ajouter dans le map
   //  std::multimap<std::string,aa::BaseClass*> m_testMapKey;
  }
} // End of namespace