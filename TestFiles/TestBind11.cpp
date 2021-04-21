
#include <cassert>
// C++ includes
#include <string>
#include <iostream>
// STL includes
#include <vector>
#include <functional>
#include <algorithm>
// Boost includes
#include <boost/assert.hpp>
// boost container library
#include <boost/ptr_container/ptr_vector.hpp>
// boost algorithms include
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/algorithm/count.hpp>
#include <boost/range/algorithm/count_if.hpp>
#include <boost/range/algorithm/for_each.hpp>  // ...
#include <boost/range/algorithm_ext/erase.hpp> // remove_erase algorithm
// Boost assign library
#include <boost/assign/list_of.hpp>
#include <boost/assign/list_inserter.hpp>
#include <boost/assign/std/vector.hpp>          // for 'operator+=()'
#include <boost/assign/ptr_list_of.hpp>
// boost range adaptors library
#include <boost/range/adaptors.hpp>            // ...
// #include <boost/range/adaptor/map.hpp>
// #include <boost/range/adaptor/filtered.hpp>    // ...
#include "../Btl_PrintUtils.hpp"

namespace cpp11 
{
	template <typename T, typename U>
	struct pair_creator //: std::binary_function<T, U, std::pair<T, U>> not supported (deprecated) in C++14
	{
		std::pair<T, U> operator()( T arg1, U arg2 ) const 
		{
			return std::make_pair( arg1, arg2 );
		}
	};

	// usage, is it possible to use "bind" to create a pair as this one 
	//std::transform( start1, end2, start2, std::bind2nd( pair_creator<int, bool>(), true ));
	// don't need to use bind for this, just need to use lambda (code below won't work/compile) 
	// std::transform( start1, end2, start2, std::bind(&std::make_pair<int,bool>,_1,_2);???
	// prefer lambda function to bind adaptor (overwrite start2) i think this code works, check it! 
	// std::transform( start1, end2, start2, [](int a,int b) { return std::make_pair(a,b);}
	// std::transform( start1, end2, start2, [](int a) { return std::make_pair(a,2);}

	// some typedef for cleaner code
	using BinaryFunc = std::function<int(int,int)>;
    using UnaryFunc = std::function<int(int)>;
    using UnaryDblFunc = std::function<double(double)>;

	// can i do that? humm!! it's a wrapper (it compiles!!)
	class myFunc : std::function<void(int)> 
	{
	public:
		// define a functor
		void operator() (int aVal) 
		{ std::cout << "Value passed as argument is: " << aVal << "\n";}
	};

	void testArgs( /*std::function<void (int)>*/ myFunc aFunc)
	{
		std::cout << "Testing new C++11 function type\n";
	}

	// lets say that i have a function that takes as argument this binary function
	void myTestStdFunc( BinaryFunc aBfunc)
	{
		// let's call this function for fun
		std::cout << "Calling Binary function and the result is: " << aBfunc(1,4) << "\n";
	}

  // take a unary function as argument but we can 
  // pass a binary with one of it's argument binded
  // converted as a unary function
  void testBinary2UnaryFunc( UnaryFunc aUFunc)
  {
    using namespace boost::assign;

    // let's create a vector of data and apply it 
    std::vector<int> w_vecInt = list_of(3)(2)(7)(2)(2);
    for (const int w_val : w_vecInt)
    {
      // call our unary function
      std::cout << "Calling Unary function and the result is: " << aUFunc(w_val) << "\n";
    }
  }

  // some basic calculation t show the concept
  void testDbl2Unary( UnaryDblFunc aDblUnaryFunc)
  {
     using namespace boost::assign;

    // let's create a vector of data and apply it 
    std::vector<double> w_vecInt = list_of(3.3)(1.2)(7.12)(4.2)(8.2);
    for (const double w_val : w_vecInt)
    {
      // call our unary function
      std::cout << "Calling Unary function and the result is: " << aDblUnaryFunc(w_val) << "\n";
    }

  }

	// generate a sequence of number 
	// (example of use: "generate_n algorithm")
	template<typename T> class NumSequence // T is the type to generate 
	{                                      // 
	public:
		// default ctor
		NumSequence( T aInitialValue=0, T aStep=1) 
		: m_Type(aInitialValue)
		{
			m_Delta = aStep;            // step as default value
		}

		// function call
		T operator () () { return m_Type+=m_Delta;}
	private:
		// Value to increment by step
		T m_Type;
		// step increment
		T m_Delta;
	};

  // used for bind test with argument
  double testBindArg( double A, double B, double C)
  {
    // compute some formula
    return (A+2.*B-1.2*C);
  }

	// Some test of the bind mechanism
	void testBindingFunc() 
	{
		using vecInt = std::vector<int>;
		using namespace std::placeholders;

		vecInt w_vec;

		// initialize the count, didn't find any yet 
		//int countBoost = 0;

		// (i > 5 && i <=10) implementation without any loop 
		// not error prone and easy to understand because of the clarity
		auto w_valInt=10;
		auto valFive = 5;
		auto countBoost = boost::count_if( w_vec,
			std::bind( std::logical_and<bool>(),              // &&
			std::bind( std::greater<int>(),    _1, valFive),   // >5
			std::bind( std::less_equal<int>(), _1, w_valInt))  // <= 10
			);

		// for_each expect a unary function, need to bind
		// what is the meaning of the 2 call? are we binding the second and then the first argument?
		std::for_each( w_vec.begin(), w_vec.end(), std::bind( std::multiplies<int> {}, _1,2)); // tied first parameter??
		std::for_each( w_vec.begin(), w_vec.end(), std::bind( std::multiplies<int> {}, 3,_1)); // tied second parameter??
		// let's give a try with plus which is also a binary function

		// 		vecint numbers;
		// 		numbers+=20,-30,10,-40,0;
		//int cx = std::count_if (numbers, numbers+5, std::bind2nd(std::greater_equal<int>(),0));
		// 		int cx = std::count_if( numbers.begin(), numbers.end(), std::bind( std::greater_equal<int>, _1, 0));
		//		std::cout << "There are " << cx << " non-negative elements.\n";

		// 		std::list<directory_entry> datFiles;
		// 		boost::copy(rng
		// 			| boost::adaptors::filtered(static_cast<bool (*)(const path&)>(&is_regular_file))
		// 			| boost::adaptors::filtered(boost::bind(std::equal_to<path>(), boost::bind(extension, _1), path(".dat"))),
		// 			std::back_inserter(datFiles));
		// 			
		// 
		// 		boost::copy( w_vec1 | filtered( std::bind( std::greater_equal<int>(),_1,5)), 
		// 			std::ostream_iterator<int>(std::cout, "\n"));
		// 			
		
		// Something that would like to test!!
		// sequence of 10 numbers starting from 0, grid nodes coordinate
    // we have w_X =  
		std::vector<float> w_X; // shall we use reserve? yes i do think so
		w_X.reserve( 10);
		std::generate_n( std::back_inserter(w_X),  // start
			             10,                       // number of elements
			             NumSequence<float>( 0.f, 10)); // generate values

		// subtract by delta because the generator increment the initial value
		// instead of starting at 0. we start at 0.1, so we have to subtract
		// x-=dx to get what we really want
// 		std::transform( w_X.begin(), w_X.end(), w_X.begin(), 
// 			std::bind2nd( std::minus<float>(),w_Discr->m_dX));
    
    // create a temporary vector for testing purpose
    std::vector<float> wTmpVec(w_X.begin(),w_X.end());

    // just a test to make sure that i do understand, i shall end up
    // with element subtracted by 2 (bind2nd version)
    std::transform( wTmpVec.begin(), wTmpVec.end(), wTmpVec.begin(),
      std::bind( std::minus<float>{},_1,2.f));

    // copy vector
    std::vector<float> w_checkVec( w_X.begin(), w_X.end());
    std::transform( w_checkVec.begin(), w_checkVec.end(), w_checkVec.begin(), 
       			std::bind( std::minus<float>{},std::placeholders::_1,2.f));

    // both ranges shall be equal (value)
    if (!std::equal(wTmpVec.begin(), wTmpVec.end(), // first range
      w_checkVec.begin())) // second range
    {
      std::cout << "I did not understand the bind adaptor\n";
    }

    // what we do here, we subtract (a-b) where a is 2 and b=w_X[i] 
    // actually we bind the first argument to 2 (as bind1st use to do), 
    // it gives negative number -8, -18,-28,-38,...,-98
		std::transform( w_X.begin(), w_X.end(), w_X.begin(),
			std::bind( std::minus<float>{},2.f,_1)); // are we really binding the second element?
                                             // No we are binding the first argument exactly
                                             // the same way we use to do with bind1st 
		
    // let's say now we want to bind the second argument, this way we should end up
    // with result such as -10, ... second argument binded as bind2nd before c++11
    std::transform( w_X.begin(), w_X.end(), w_X.begin(),
      std::bind( std::minus<float>{},_1,2.f));

    std::cout << "Printing grid node coordinate\n";

		std::copy( w_X.begin(),w_X.end(),
			std::ostream_iterator<float>(std::cout," "));
		
		std::cout << "\n";
	}

	// some test about the bind mechanism implemented in the new c++11
	void testBindType()
	{
		using namespace Btl;
		using namespace std::placeholders;
		using namespace boost::adaptors;
		using namespace boost::assign;

		using Pair = std::pair<int,int>;

		// can i do a typedef on the bind mechanism?
		// below what we do, we are assigning a functor (bind) 
		auto choose_first = std::bind( &Pair::first, _1);

	    //  can i call it this way?
		choose_first(std::make_pair(1,2));

#if 0
		// Create a vector of pointer
		std::vector<int*> w_vecptrInt; 
		w_vecptrInt += list_of<int*>( new int(1))( new int (2))( new int(6))( new int(3));
		assert( w_vecptrInt.size() == 4);
		auto w_first = w_vecptrInt.back();
		std::cout << "The type of the pointer is " << typeid(w_first).name() << "\n";
		std::cout << "The value of the first element is " << *w_first << "\n";
		if( !w_vecptrInt.empty())
		{
			// delete each element of the container in a simple manner
			// std::for_each( std::begin(w_vecptrInt),std::end(w_vecptrInt), 
			// 	std::bind(::operator delete, _1)); not compile, complaining about template deduce 
			std::for_each( std::begin(w_vecptrInt),std::end(w_vecptrInt), 
			[] ( int* aIntPtr)
			{
				if( aIntPtr != nullptr)
				{
					delete aIntPtr;
					aIntPtr=nullptr;
				}
			});
		}
#endif

		// this won't work because the "ptr_list_of"  
		// works only with the boost ptr_container
// 		std::vector<int*> w_ag12;
// 		w_ag12=ptr_list_of<int*>(new int(1));

		// ptr_list_of is used with the ptr container of boost
		// don't need to call new manually for each element
		// don't need to call delete when it goes out of scope
		struct Foo {
			Foo() :i{} {} 
			Foo(int aI): i{aI} {}
			int i;
			};
//		boost::ptr_vector<Foo> w_testPtrListOf;
//		w_testPtrListOf = ptr_list_of<Foo>(),(1),(2);

//		BOOST_ASSERT( w_testPtrListOf.size() == 3 );
		
		// create a pair vector for testing
		std::vector<Pair> w_vofpair = pair_list_of(1,2)(2,3)(21,5)(3,6);
		std::list<Pair::first_type> w_keyList;
    // way to print the key of the pair element very efficiently
		for( auto& first : w_vofpair | map_keys) // range loop
		{
			// copy to range
			w_keyList.push_back(first);
		}
		assert( w_keyList.size() == w_vofpair.size());

		std::vector<int> start1 = list_of(1)(2)(3)(4)(5);
		std::vector<int> start2 = list_of(10)(20)(30)(40)(50);
		std::vector<Pair> w_vecofpair; // just to make sure that we start with brand new vec
		w_vofpair.reserve(start1.size()); // ...
	  
    // create pair using lambda
		std::transform( std::begin(start1), std::end(start1), std::begin(start2), // ranges 
			std::back_inserter(w_vecofpair),  // result 
			[] (int a,int b) { return std::make_pair(a,b);}); // pair creator
	
		for ( auto& pairInt : w_vecofpair)
		{
			std::cout << pairInt << "\n"; 
		}

		// bind 2nd arg to some value, say 2
		std::transform( std::begin(start1), std::end(start1), std::begin(start2), 
			std::back_inserter(w_vecofpair), [](int a, int b) { return std::make_pair(a,2);});

		for (auto& second : w_vecofpair | map_values)
		{
			std::cout << "The second value of our bind 2nd is: " << second << "\n";
			assert(second==2);
		}

		// create a map
	//	std::map<std::string,int> w_mapstrint;
	}

	// some test that i have found useful that i didn't know
	// functional stuff ()
	void someBindTest()
	{
    using namespace std::placeholders;
    using namespace boost::assign;
    using namespace std;

		// create an instance
		std::plus<int> w_stdPlus;
		// call the "operator()" ...
		std::cout << "The result of plus functor is: " << w_stdPlus(1,1) << "\n";
		
    // let's use the binder mechanism provided by C++11 (thanks to Boost)
		// what we doing here, we are simply creating a binary functor with its 
		// second arg bind to 2 (adapter that make a binary looks like a unary)
		// it's more bind2nd argument than bind1st
    auto w_plusbind2nd = std::bind( std::plus<int>{}, _1,_2);
//     std::transform(start1.begin(),start1.end(),std::back_inserter(w_res),
//       std::bind(std::minus<int>(),1,_1));

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    // Initialize vector with list initializer (boost assign library)
    std::vector<int> range1 = list_of(-1)(2)(5)(6)(-3);
    std::vector<int> w_res;
    w_res.reserve(5);

    // define a binary function and initialize it 
    // (same as bind2nd which is now deprecated since C++11)
    auto w_minusBind2nd = std::bind(std::minus<int>(),1,_1);
    // stl algorithm
    std::transform(range1.begin(),range1.end(),
      std::back_inserter(w_res),
      w_minusBind2nd);
    
    // print result (2,-1,-4,-5,4)
    std::copy( w_res.begin(), w_res.end(),
      std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";

    // let's do the same with the first argument 
    // (same as bind1st which is now deprecated since C++11)
    auto w_minusBind1st = std::bind(std::minus<int>(),_1,1);

    // capacity still the same but size is now zero
    w_res.clear(); 

    // apply function to data
    std::transform( range1.begin(),range1.end(),std::back_inserter(w_res),
      w_minusBind1st);

    // print result (-2,1,4,5,-4)
    std::copy(w_res.begin(),w_res.end(),
      std::ostream_iterator<int>(std::cout, " "));

    std::cout <<"\n";
    w_res.clear();
    
    // passing theses function to C-function as argument

    // we can also pass it as single argument function ()
    testBinary2UnaryFunc(w_minusBind1st);

    // pass as argument to a function (first argument bind to 1)
    myTestStdFunc( w_plusbind2nd); // looks like is taking the binding even 
                                   // if i call the binary inside the function

    // on-the-fly argument (pre-defined function object)
    myTestStdFunc( std::bind( std::plus<int>(),1,4));

    // ++++++++++++++++++++++++ writing my own function object 
    // (a simple algorithm that perform some math computation)
    // void testBindArg( double A, double B, double C) 3 args 
    auto w_testBindArgs = bind( &testBindArg,_1,1.4,3.2); // become unary function

    // pass it as an argument ()
    testDbl2Unary(w_testBindArgs);

    // define another range another range 
    vector<double> rangedbl1 = list_of(0.)(1.4)(8.3)(0.6)(-3.3);
    vector<double> rangedbl2(rangedbl1.size()); // store result 
    //rangedbl2.reserve(rangedbl1.size());
    
    // use it with transform algorithm and pass it as a binary function
    // binding one argument
    transform( begin(rangedbl1),end(rangedbl1),begin(rangedbl2),
      back_inserter(rangedbl2), // store result of the algorithm
      w_testBindArgs); // now it's a unary function with second argument bind to 2

    // create a vector of function
    // same signature as testDbl2Unary() 
    typedef function<double(double)> func3args2one;
    vector<func3args2one> w_vecofFunc;
    w_vecofFunc.reserve(3);

    // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // NOTE we have our list of section flow and want to compute 
    // the geometric property of each section like WettedArea,
    // and so on, H=A-Z with Z=1. and B=1.
    // Check if our section are flat bed and unit width
    // ... to be completed
    // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    // convert 3 args function as a unary function and add it to the container
    w_vecofFunc.push_back( bind(&testBindArg,_1,1.4,3.2)); // bind second and third arg
    w_vecofFunc.push_back( bind(&testBindArg,1.2,3.2,_1)); // bind what??
    w_vecofFunc.push_back( bind(&testBindArg,2.1,_1,3.2)); // what we do here

    // retrieve function from vector of function 
    func3args2one w_checkAgain = w_vecofFunc[0];
    w_checkAgain(0.5); // calling as a unary function

    vector<double> w_rngDbl;
    w_rngDbl += 0.2,1.6,2.3,9.2,4.; //list_of(0.2)(1.6)(2.3)(9.2)(4.);
    
    vector<double> w_resDbl1;
    w_resDbl1.reserve(w_rngDbl.size());

    // now loop on each function and test the result
    for( func3args2one myFunc : w_vecofFunc)
    {
      // calling the algorithm for each of these function with different binding
      transform( begin(w_rngDbl), end(w_rngDbl), // range
        back_inserter(w_resDbl1), // store result 
        myFunc); // calling function or the algorithm

      // print result (could store result in a file for visualizing later)
      copy( begin(w_resDbl1),end(w_resDbl1),ostream_iterator<double>(cout, " "));
      cout << "\n";
      w_resDbl1.clear(); // empty vector and prepare for next iteration
    }

    // ++++++++++++++++++++++++++++++++++++++++++++++++++++++

    std::cout << "Let's call my Binder1st for fun: " << w_plusbind2nd(1,2) << "\n";
		// fill vector with 1's
		std::vector<int> w_vcInt(5,1);
		
    // unless i miss something we shouldn't find anything
		auto w_foundfPos = std::find_if( std::begin(w_vcInt), std::end(w_vcInt),
			std::bind( std::greater<int>(),std::placeholders::_1,1));
		
    // just in case i really miss something (find_if algorithm as many stl algorithm)
		// will return end if it doesn't succeed 
		assert(w_foundfPos == std::end(w_vcInt));
		std::cout << "We did our test successfully and continue exploring\n";
    
    // that can be used with simple range
    std::vector<double> w_rangeDbl1 = list_of(1.)(0.3)(3.2)(12.3)(-0.5);
    std::vector<double> w_resDbl;
    w_resDbl.reserve(w_rangeDbl1.size());
    std::transform( w_rangeDbl1.begin(),w_rangeDbl1.end(),std::back_inserter(w_res),
      w_testBindArgs);

    // i don't see why i can't (without the the parenthesis, i..e. ctor call)
		// it doesn't compile. Need to call the ctor. Actually we are doing the 
		// same thing when we use the bind(), what we do behind the hood, call 
		// the ctor (create a functor), because bind return bind_t ctor with 
		// arguments to bind 
		auto w_chk = std::plus<int>(); // 
		
		/*			I am trying to remove short strings from a vector.*/
		//				std::vector<std::string> vec;
		// instead use std::bind
		// 			vec.erase( std::remove_if(vec.begin(),
		// 				vec.end(),
		// 				boost::bind( std::less<size_t>(),
		// 				boost::bind( &std::string::length, _1),
		// 				5),
		// 				vec.end());

		//		The following solution works:
		// 			vec.erase( std::remove_if(vec.begin(),
		// 				vec.end(), // physical end
		// 				boost::bind(&std::string::length, _1) < 5),
		// 				vec.end()); // logical end
	}
} // End of namespace