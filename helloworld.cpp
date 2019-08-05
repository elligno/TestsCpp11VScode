
// C++ includes
#include <string>
#include <iostream>
#include <cstdlib>
#include <chrono>
// STL includes
#include <vector>
#include <algorithm>
// boost include
#include <boost/cast.hpp>
// test include
#include "Classes/Class2Test.h"

// delaring some global function or variables
namespace vs11
{
    void testBindMechanism();
    void testToAddFile();
    void testingShardPtr();  
    void testClassBond();  
    void testBase();
    void testMvCall();
    void testInitialization();
	void stlTest();
}

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


// =======================================================
//
//               Windows main entry point
//
// =======================================================

int main()
{
	using namespace std;

    std::cout << "Starting tetsing with VSCode, continuing to configure my environment\n";

	// For measuring the execution time of a piece of code, 
	// we can use the now() function:
    auto start = chrono::steady_clock::now();

    //
    //  Insert the code that will be timed
    //  
    auto end = chrono::steady_clock::now();
  
    // Store the time difference between start and end
    auto diff = end - start;

	// can now include boost header 
	const double myDbl=0.3;
	const int dbl2int = boost::numeric_cast<int>(myDbl);
	std::cout << "i surely can\n";

	// some test about casting down hierarchy (casting base) 
	vs11::testClassBond();

    // just a test
    testInvertStringChar(); 
    vs11::testInitialization();

    // Quiz test 
   // vs11::testMvCall();
    vs11::testBindMechanism();
    vs11::testBase();

  //  vs11::StaticVarTest w_checkCall;
  //  vs11::StaticVarTest::m_sVar = 2;

    std::cout << "Starting debugging with VSCode\n";

    // not sure i do understand the difference between them 
	// what we should do? new notation or old one?
    int ii = {}; // what we do exactly? call a ctor? default one
    int jj = int(); // default initialization
   // int kk;

  //vs1::testingShardPtr();
//    vs1::testToAddFile();
    
    std::cout << "Hello World!";
}