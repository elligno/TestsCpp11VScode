
// C++ includes
#include <string>
#include <iostream>
#include <algorithm>
#include <valarray> // numerical array (efficiency)
#include <array>
#include <set>

// boost includes
#include <boost/cast.hpp>
// test include
#include "Classes/Class2Test.h"
#include "Classes/myMoveClass.h"
#include "Classes/myStringClass.h"
#include "Classes/ClassVS15.h"
//#include "Classes/TmxString.h"

// declaring some global function or variables
namespace vs11
{
    //void testBindMechanism();  test virtual ...
    //     void testToAddFile();
    //     void testingShardPtr();
    void testClassBond();
    void testBase();
    void testMvCall();
    //     void testInitialization();
    void validateMStest();
    // 	void stlTest();
    void testClassBond();
    std::unique_ptr<int[]> retUniquePtrArray();
    void CtorInit();
    void findDuplicateTest();
} //vs11

namespace cpp11  
{
    vs15::MoveTest checkSomeNvFeatures();
    void testSmartPointer();
}//cpp11

namespace SfxType 
{
    void testScalarField(); 
}//SfxType

namespace vs15 { int maxProfit( int price[], int start, int end);}

// signature should be char s[]??
// because strlen(char*) is it the same as strlen(s[])?
// i don't think so, need to check
void invertStr(char *aStr2Invert)
{
    using namespace std;

    cout << "we are ready to invert the string\n";

    // just a basic test to invert a string
    // IMPORTANT don't forget to subtract 1 because
    // of the null terminated character for C string
    for (size_t i = 0, j = ::strlen(aStr2Invert) - 1; i < j; ++i, --j)
    {
        int w_char = aStr2Invert[j];
        aStr2Invert[j] = aStr2Invert[i];
        aStr2Invert[i] = w_char;
    }

    cout << "We just finished to invert the string\n";
}

void testInvertStringChar()
{
    char *w_charPtr = "jeanb";                // when i do this, i just set a pointer to string
                                              // problem we have a pointer to a string and not a
                                              // not a string which is an array of char (iterable)
    char *w_charAlloc = new char[6]{"jeanb"}; // we have an array of char (string)
    invertStr(w_charAlloc);
    std::cout << "Test inverting a char pointer with allocated is: " << w_charAlloc << "\n";
    delete[] w_charAlloc;
    std::string w_teststrInv("jeanb");
    char w_charArr[6] = "jeanb";
    invertStr(w_charArr);
    std::cout << "Inverted arrays of char is: " << w_charArr << "\n";
    invertStr(const_cast<char *>(w_teststrInv.c_str()));
    std::cout << "Inverted string is: " << w_teststrInv << "\n";
}

// Just want to check the conversion from C string to myStringClass
// when calling checkTmpObj("asdsafd"); const char* implicit conversion
// we pass as arg a C-string but expect myStringClass
// it has a ctor that takes C-string and convert it to myStringClass
// but need to create a tmp object? is what happens?
void checkTmpObj(const vs15::myStringClass &aStr)
{
    std::cout << "We are in the checkTmpobj() function\n";
    //just a test about print char pointer
    const char *w_checkPrint = "abcdef";
    std::cout << w_checkPrint << "\n"; // print char directly
}

std::string getFruitVite( unsigned val)
{
    // declare 4 elements but initialize with 5, error too many initializer
    std::array<std::string, 4> fruitsDispo{ "Pas bon fruit", "Banane", "Pomme", "pas bon fruit"/*, "Poire"*/};
    if( val < fruitsDispo.size())
        return fruitsDispo[val];

    return fruitsDispo[0];
}

std::vector<std::string>& GetAllUnsignedShorts()
{
    // actually u should use reserve for memory managemnet
    // here we have a vector of 65536 element initialized to zero
    // but pushing back u just add element at the end of the vector and u endup with twice as much element
   static std::vector<std::string> tableau(65536);      // reserve space!  environ 1.5 meg!!!
   if( tableau.empty())
   {
       for( auto i = 0; i < 65536; ++i) //i++ initially avoid temp object 
         tableau.push_back( std::to_string(i));
   }
   return tableau;
}

std::string IntToString1( unsigned short val)
{
     static const std::vector<std::string>& tableau =  GetAllUnsignedShorts();     // first time only init
     return tableau[val];    // constant time!!!!   so we think!
}

//vs:
std::string IntToString2( unsigned short val)
{
     return std::to_string(val); // does it call move ctor of string avoid temporary object creation from copy?
}

void myFuncByVal( vs15::Classvs15 aParam) 
{
    std::cout << "Pass arg by value\n";  // param is initialized by passed argument
}

vs15::Classvs15 myFuncRetVal()
{ 
    return vs15::Classvs15 {}; // return temporary (no call to move ctor)
}

// Some class test brain storming
// A Simple C++ program to compute sum of digits in numbers from 1 to n

// forward declaration 
bool has4(int x, int digit2Cmp);

// Returns sum of all digits in numbers from 1 to n
int countNumbersWith4(int n)
{
  int result = 0; // initialize result

  // One by one compute sum of digits in every number from
  // 1 to n
  for( auto i = 1; i <= n; ++i)
    result += has4(i,4) ? 1 : 0;

  return result;
}

// A utility function to compute sum of digits in a
// given number x
bool has4( int x4, int digit2Cmp)
{
  while( x4 != 0)
  {
    // debug purpose
    auto res = x4 % 10;

    if( x4 % 10 == digit2Cmp)
      return true;

    x4 = x4 / 10;
  }

  return false;
}

// =======================================================
//
//               Windows main entry point
//
// =======================================================

int main()
{
    #if 0
    std::array<int,10> w_arr1 { 1,2,3,3,4,7,1,4,5,6};
    std::array<int,10> w_arr2 { 1,2,3,4,3,2,7,7,8,9};

    std::set<int> w_sortedRng1( w_arr1.cbegin(), w_arr1.cend());
    std::set<int> w_sortedRng2( w_arr2.cbegin(), w_arr2.cend());

    std::vector<int> w_vecRes; w_vecRes.reserve(5);
    std::set_intersection( w_sortedRng1.cbegin(), w_sortedRng1.cend(),
     w_sortedRng2.cbegin(), w_sortedRng2.cend(), std::back_inserter(w_vecRes));
#endif
     // 
     vs11::findDuplicateTest();

    // auto is pointer type? yes it does!!
    auto p = new char[20];  
    p[0] = 'a'; // do i need to delete?
    std::cout << "auto pointer value is: " << *p << "\n"; 
    if( nullptr != p) { delete p; p = nullptr;}
#if 1
    // copy elison C++17 (copy/move ctor deleted it should not compile, it is!!)
    // allowed move only and copy ctor deleted, it compile and works, but never
    // the move ctor is called but it needs to exist (below casess with temporaries).
    myFuncByVal( vs15::Classvs15 {});            // use temporary to initalize param
    vs15::Classvs15 w_checkRet = myFuncRetVal(); // use returned temporary to initialize w_chekRet
    myFuncByVal( std::move(myFuncRetVal()));                 // use returned temporary to initialize param

    vs15::Classvs15 w_mvClazz = std::move(w_checkRet);
#endif

    auto w_fruitRet = getFruitVite(4);
    // create a vector of 5 elements initiated to 0
    std::vector<double> w_vec(5);
   // const auto w_siz = w_vec.size(); error about initalization of const w_siz 
    w_vec.push_back(2);
    assert( 6 == w_vec.size());
    
    // brace initialization vector of one element set to 5? is that true?
    // it sure is!! vector of size 1 with value 5
    std::vector<double> w_braceVec {5};
    assert(1==w_braceVec.size());
    std::cout << "Vector value is: " << w_braceVec[0] << std::endl;

    const char w_ch[] = "eqdsadsadwasdrwer";
    const char* w_chptr = "rwer";
    auto chk1 = sizeof(w_ch); // sizeof of an array 
    auto chk2 = sizeof(w_chptr); // sizeof of a pointer, 8 on x64 architecture
    auto chk11 = ::strlen(w_ch);
    auto chk12 = ::strlen(w_chptr);
    // char* w_strDup = ::strdup(w_chptr);
    // free(w_strDup);
 
    // Tmx string
    // vs15::TmxString w_jeanTest; // empty string as default
    // vs15::TmxString w_cpyJeanStr = w_jeanTest; // copy ctor
    // std::cout << "Jean Tmx test string " << w_cpyJeanStr.c_str() << "\n";
    // vs15::TmxString w_ctor("JeaanBel");
   // (w_jeanTest = w_ctor) = w_cpyJeanStr = "sasd";

    vs15::myStringClass w_testStr("asdasd"); // const char[]
    std::cout << "String is " << w_testStr.data() << "\n";
    vs15::myStringClass w_cpyStr = w_testStr;
    std::cout << "Copy string is: " << w_cpyStr.data() << "\n";

    // call with a const char it shall create a temporary object
    // for the implicit conversion to myStringClass  
    checkTmpObj("Char2Str"); // const char* 

    // Numerical library test/validation
    SfxType::testScalarField();

    // does it call move ctor? yes it does since we have a rvalue 
    // (call function) return by value create a temporary object
    vs15::MoveTest w_checCpy = cpp11::checkSomeNvFeatures();

    // return smart pointer (unique by move semantic)
    auto w_uniqArr = vs11::retUniquePtrArray();
    for( auto i = 0; i < 5; i++) // assume 5 elements
    {
        std::cout << "Array value is: " << w_uniqArr[i] << "\n"; 
    }
  
//    vs11::testBase();
    // vs11::CtorInit();
    // vs11::validateMStest();
    // std::cout << "Finished MS test" <<"\n";

 //  vs11::SomeClass cpyCall = somefunction();
 //  int staVar = cpyCall.getStaticVar();

   // default ctor 
   //std::shared_ptr<vs11::SomeClass> w_testCpy(nullptr);

	// some test about casting down hierarchy (casting base)
//	vs11::testClassBond();

    // just a test
 //   testInvertStringChar();
 //   vs11::testInitialization();

    // Quiz test
    vs11::testMvCall();
 //   vs11::testBindMechanism();
 //   vs11::testBase();

    // not sure i do understand the difference between them
	// what we should do? new notation or old one?
    // braces initialization is call direct list initialization
    // uniform initialization from C++11 and ensure zero initalization
    // The second one is the usual initalization (default ctor call)
    // and set to zero, should prefer the new braces 
    int ii = {}; // what we do exactly? call a ctor? default one
    int jj = int(); // default initialization
   // int kk;

  //vs1::testingShardPtr();
//    vs1::testToAddFile();

	// returning safely from main application 
	return EXIT_SUCCESS;
}