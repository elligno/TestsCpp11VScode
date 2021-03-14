
// C++ includes
#include <iostream>
#include <utility> // pair and tuple
#include <tuple>
#include <string>
// stl include
#include <vector>
#include <algorithm> // std algorithm
#include <functional>
// boost include
#include <boost/assign/std/vector.hpp> // '+=' for assign
#include <boost/range/iterator_range.hpp> // iterator range library

namespace cpp11 
{
	/**
	 * @brief pair of this class no compile 
	 * 
	 */
	class A 
	{
	public:
		A() {} // without this it does not compile
		A( A& aOther) {} // copy ctor with non-constant reference
	};

	// testing pair and tuple
	class Foo1 
	{
	public:
		Foo1( std::tuple<int,float>) { std::cout << "Foo1::Foo1(tuple)" << "\n";}
		Foo1(int aInt, float aFloat) { std::cout << "Foo1::Foo1(int,float)";    }
	};

//   template <typename T, typename U>
//   struct pair_creator : std::binary_function<T, U, std::pair<T, U>>
//   {
//     std::pair<T, U> operator() ( const T& arg1, const U& arg2 ) const 
//     {
//       return std::make_pair( arg1, arg2 );
//     }
//   };

	// _________________________________________________________________
	//
	//  Testing pair and tuple
	void someTestCpp11()
	{
		// just testing new features of the cpp11
		// create a pair
		std::pair<std::string,int> w_pair1 = std::make_pair( std::string("Test123"),1);

		// print pair values by using new C++11 features
		// tuple interface get<...>()
		std::string w_check1 = std::get<0>(w_pair1); // first
		int w_check2 = std::get<1>(w_pair1);         // second

		// create pair of integer and then compare (first and second)
		auto w_pairInt1 = std::make_pair( 1,1);
		auto w_pairInt2 = std::make_pair( 1,1);

		// test for equality
		if( w_pairInt1 == w_pairInt2)
		{
			std::cout << "Pair are equal\n";
		}

		// new cpp features (create a pair of reference)
		int i=0;
		auto w_pairRef = std::make_pair( std::ref(i), std::ref(i));
		++w_pairRef.first;
		++w_pairRef.second;
		// value shall be 2
		std::cout << "Value is now: " << i << "\n";

		// now print value
		//std::tuple<int,double,std::string> w_testTuple(1,2.3,"Jean");

		// test the "bind" adapter (no need to add space to template > > at the end)
		typedef std::pair<int,int> pairofint;
		typedef std::vector<std::pair<int,int>> vecofpair; // vector of pair
		vecofpair w_vecofInt(5);                           // initialize to zero (default ctor)
		int j(0);
		vecofpair::size_type w_vecSize=w_vecofInt.size();  // shall be equal to 5
		w_vecofInt[j++] = std::make_pair(1,2);
		w_vecofInt[j++] = std::make_pair(1,3);
		w_vecofInt[j++] = std::make_pair(1,4);
		w_vecofInt[j++] = std::make_pair(1,5);
		w_vecofInt[j]   = std::make_pair(2,2);

		// shall use the boost assign library for initialize the vector!!

		// Range loop feature of Cpp11
		for( const auto& elem : w_vecofInt)
		{
			// using the new feature of C++11 std::get<>() 
			std::cout << "First element is: " << std::get<0>(elem) << "  " 
				<< "Second element is: " << std::get<1>(elem) << "\n"; 
		}

		std::cout << "\n";
		std::cout << "Now trying with lambda function\n";
		
		// same thing but by using the lambda function
		std::for_each( w_vecofInt.begin(), w_vecofInt.end(),
			[] ( pairofint aPair)
		{
			std::cout << "First element is: " << std::get<0>(aPair)  << " "
				<< "Second element is: " << std::get<1>(aPair) << "\n";
		});

		std::pair<A,int> p; // class with only non-constant copy ctor don't compile

		typedef std::pair<int,float> IntFloatPair;
		IntFloatPair w_pair(42,1.23f); // create a pair
		
		// check size by using the new C++11 feature about pair and tuple
		std::cout << "Size of pair is: " << std::tuple_size<IntFloatPair>::value << "\n";

		// copy and assignment ctor
		typedef std::pair<int,int> pairint;
		pairint w_p1(1,2);
		pairint w_p2(4,1);
		pairint w_p3=w_p1; // copy ctor
		if (w_p3!=w_p1) // shall be equal
		{
			std::cout << "Something wrong with copying pair\n";
		}
		
		pairint w_p4( std::move(w_p1)); // move semantic, w_p1 shall be no more useable
		
		// ...
		std::tuple<int,float> w_tupl(1,2.23f); 
		std::pair<int,Foo1> w_pt(42,w_tupl);   // pass the tuple to Foo1 ctor

	    //	std::pair<int,float> w_typeCheck(1,2.45);
		auto w_pp1 = std::make_pair( 1, 2.45); // double as second (implicit conversion)
		// float w_fl;  warning when extracting the second argument
		double w_dbl;
		std::tie( std::ignore,w_dbl)=w_pp1;

		std::tuple<int,float> w_testTpl( 1, 2.56f);
		// i am not sure i understand the meaning of "piecewise construct"  
		std::pair<int,float> w_pfromt( std::piecewise_construct, std::make_tuple(42), 
			                           std::make_tuple(3.f)); 
	}

	void testCreatingPair()
	{
		using namespace std::placeholders;
		using namespace boost;
		using namespace boost::assign; // assign library

		std::vector<int> w_vecInt1{1, 2, 3, 4, 5, 6, 7, 8};
		//w_vecInt1+=1,2,3,4,5,6,7,8;
		std::vector<std::pair<int, int>> w_pairOfInt;

		// creating range that are offset to make pair
		using vec_range_iter = boost::iterator_range<std::vector<int>::iterator>;

		// [begin,end-1[
		vec_range_iter w_rng1 = boost::make_iterator_range( w_vecInt1.begin(), w_vecInt1.end()).advance_end(-1);
		// [begin+1,end[
		vec_range_iter w_rng2 = boost::make_iterator_range( w_vecInt1.begin(), w_vecInt1.end()).advance_begin(1);

		// now we have two range with element that are offset by 1
		assert(w_vecInt1.size() - 1 == w_rng1.size()); // new range
		assert(w_vecInt1.size() - 1 == w_rng2.size()); // new range

        // need to write a lambda function instead
		
		// // using the transform algorithm with bind adaptor (C++11)
		// std::transform( w_rng1.begin(), w_rng1.end(), w_rng2.begin(),
		// 			    w_pairOfInt.begin(), std::bind(pair_creator<int, int>(), _1, _2));

		//		int x[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
		// i should have a warning about safe iterator or something like that
		//		std::copy( x, x+8, std::ostream_iterator<int>(std::cout, " "));
		//	std::copy( x, x+(sizeof(x)/sizeof(int)), std::ostream_iterator<int>(std::cout," "));

		// C++11 version more safe and clean, it really shows the programmer intent
		// this new functionality of C++11 really help a lot to make better code
		// it's clear, i am going through the array from the beginning to the end, that's it, that's all!!!
		// ... add a comment
		// this line doesn't compile, complaining about non safe iterator or something like that 
		//	std::copy( std::begin(x), std::end(x), [](int i){std::cout << i << " ";});
	}
}