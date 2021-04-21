
// C++ includes
#include <string>
#include <iostream>
#include <algorithm>
#include <valarray> // numerical array (efficiency)

//#include <cstdlib>
//#include <chrono>
// STL includes
//#include <vector>
//#include <algorithm>
// boost includes
#include <boost/cast.hpp>
// test include
#include "Classes/Class2Test.h"
// Numeric library includes
#include "jb_scalarField.h" // include grid lattice
#include "ElgoPtr.h" // in house smart pointer impl
#include "PhysCte.h" // some physical constant

// declaring some global function or variables
namespace vs11
{
     //void testBindMechanism();  test virtual ...
//     void testToAddFile();
//     void testingShardPtr();
     void testClassBond();
//     void testBase();
//     void testMvCall();
//     void testInitialization();
// 	void stlTest();
void someSharedPtr( std::shared_ptr<int> aX);
void someUniqPtr( std::unique_ptr<int> aX);
void someMS(int* aX);
}//vs11

	// signature should be char s[]??
	// because strlen(char*) is it the same as strlen(s[])?
	// i don't think so, need to check
	void invertStr( char* aStr2Invert)
	{
		using namespace std;

		cout << "we are ready to invert the string\n";

		// just a basic test to invert a string
		// IMPORTANT don't forget to subtract 1 because
		// of the null terminated character for C string
		for( size_t i = 0, j = ::strlen(aStr2Invert)-1; i < j; ++i,--j)
		{
			int w_Char = aStr2Invert[j];
			aStr2Invert[j] = aStr2Invert[i];
			aStr2Invert[i] = w_Char;
		}

	 	cout << "We just finished to invert the string\n";
    }
    void testInvertStringChar()
	{
		char* w_charPtr = "jeanb"; // when i do this, i just set a pointer to string
		                           // problem we have a pointer to a string and not a
		                           // not a string which is an array of char (iterable)
		char* w_charAlloc = new char[6]{"jeanb"}; // we have an array of char (string)
		invertStr(w_charAlloc);
		std::cout << "Test inverting a char pointer with allocated is: " << w_charAlloc << "\n";
		delete [] w_charAlloc;
		std::string w_teststrInv("jeanb");
		char w_charArr[6] = "jeanb";
		invertStr(w_charArr);
		std::cout << "Inverted arrays of char is: " << w_charArr << "\n";
		invertStr(const_cast<char*>(w_teststrInv.c_str()));
		std::cout << "Inverted string is: " << w_teststrInv << "\n";
	}

   vs11::SomeClass somefunction()
   {
	   vs11::SomeClass myClass;
	   return myClass;
   }

// =======================================================
//
//               Windows main entry point
//
// =======================================================

int main()
{
   int* w_y = new int(20);
   vs11::someMS(w_y);
   std::cout << "Value of y is: " << *w_y << "\n";

   // Testing boost library cast operator
   int aa=1;
   try
   {
       float bb = boost::numeric_cast<float>(aa);
   }
   catch( const boost::bad_numeric_cast& e)
   {
       std::cerr << e.what() << '\n';
   }
   // some sanity check
   std::cout << "integer value is: " << aa << "\n";
   std::cout << "float value is: " << aa << "\n";

   //
   // Testing our library (numeircal basic type) 
   //
   
   // Base numerical library type
   std::cout << "Test linking with BaseNumTypes library\n";
   const double test = basenum::PhysicalConstant::sGravity;
   std::cout << "Gravity value is: " << test << "\n";

   // create a grid with E. McNeil discretization (dx=10., x0=0, xN=1000)
   // Node index from i=1,..,100
   std::shared_ptr<jb::gridLattice> w_grid = // E McNeil discretization as default
	   std::make_shared<jb::gridLattice>( std::string("d=1 [0,1000] [1:100]"));

   // checking some values (x=0.)
   const double checkXmin = w_grid->xMin(1); //one dimensional
   auto checkXmax = w_grid->xMax(1); //no need

   // create a scalar field for testing our VSCode environment
   std::shared_ptr<jb::scalarField> w_U12( new jb::scalarField(w_grid, std::string("A")));
   const std::string w_fieldName = w_U12->name();
   if( !w_fieldName.empty())
   {
	   std::cout << "Filed name is : " << w_fieldName << "\n"; 
   }
   // checking default values of our scalar field
   jb::RealNumArray<real> myValArray = w_U12->values();

   // default ctor 
   std::shared_ptr<vs11::SomeClass> w_testCpy;
   
   // numerical array for dfaast floating point computation
   std::valarray<double> w_testVarray(0.,10);
   auto checkIter = begin(w_testVarray);

   // Create scalar field for the A-variable
   // smart pointer
   //    elgo_ptr<int> myElgoPtr(); // default implementation with null ptr
   //    // checking support comparison operator
   //    if( myElgoPtr != nullptr)
   //    {
   // 	   std::cout << "Elgo smart pointer support comparison op\n";
   //    }

   vs11::SomeClass cpyCall = somefunction();
   int staVar = cpyCall.getStaticVar();
   //   using namespace std;

   //  std::cout << "Starting tetsing with VSCode, continuing to configure my environment\n";

   // For measuring the execution time of a piece of code,
   // we can use the now() function:
   // auto start = chrono::steady_clock::now();

    //
    //  Insert the code that will be timed
    //
    //auto end = chrono::steady_clock::now();//

    // Store the time difference between start and end
    //auto diff = end - start;

	// can now include boost header
//	const double myDbl=0.3;
//	const int dbl2int = boost::numeric_cast<int>(myDbl);
	//std::cout << "i surely can\n";

	// some test about casting down hierarchy (casting base)
//	vs11::testClassBond();

    // just a test
 //   testInvertStringChar();
 //   vs11::testInitialization();

    // Quiz test
   // vs11::testMvCall();
 //   vs11::testBindMechanism();
 //   vs11::testBase();

  //  vs11::StaticVarTest w_checkCall;
  //  vs11::StaticVarTest::m_sVar = 2;

 //   std::cout << "Starting debugging with VSCode\n";

    // not sure i do understand the difference between them
	// what we should do? new notation or old one?
    int ii = {}; // what we do exactly? call a ctor? default one
    int jj = int(); // default initialization
   // int kk;

  //vs1::testingShardPtr();
//    vs1::testToAddFile();

	// 
	const char* const w_myString="jean";
	
	// some test with constant expression
	size_t w_sizeStr = ::strnlen_s(w_myString,5);

	// i am not sure what a constant expression is exactly
	// see  appendix of Wilson book about C++ Concurrency
	// below an example of us of the constant expression usage 
	constexpr int w_intExpr = 2; // C++11
	constexpr unsigned w_arraySize = 5;
	unsigned w_arrSize = 4;
	char w_myArray[w_arraySize];
	unsigned i = 0;
	w_myArray[i++] = 'a';

	//char w_anotherArray[w_arrSize];  not a constant expression (compile error)

	std::cout << "Testing VS2015 new setup\n";

	// create an alias (typedef is now deprecated)
	using ptr2int = std::unique_ptr<int*>; // smart pointer

	// good practice is  to use the make_unique utility (see Scott Meyer's book)
	ptr2int w_testMakeUnique = std::make_unique<int*>(/*new int*/);
	if( w_testMakeUnique)
	{
		std::cout << "We have a unique pointer declared with an alias\n";
	}

	std::cout << "make unique supported with vs2015\n";

	// check if we can list initializer 
	std::vector<int> w_listVec = {1,2,43,4,5 };
	if( w_listVec.size()==5)
	{
		std::for_each( std::begin(w_listVec), std::end(w_listVec), 
			[](int aInt2Pritnt) 
		{
			std::cout << "Value is:" << aInt2Pritnt << "\n"; 
		});
	}

    std::cout << "Hello World!";

	// returning safely from main application 
	return EXIT_SUCCESS;
}