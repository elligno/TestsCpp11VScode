
// C++ includes
#include <cstdlib>  // EXIT_FAILURE
#include <iostream>
#include <fstream>
#include <string_view> // C++17 feature
#include <ranges>      // C++20 feature
#include <algorithm>   // ranges algorithm C++20
#include <compare>     // spaceship operator
#include <concepts>    // ...??? ranges

// not sure about all those includes
#include <vector>

// app. includes
//#include "Global.h"
#include "Classes/testSfx_Global.h"

// Using module C++20 feature
//import std.regex;  need to install module library from VS19 installer
// from "Individual Tab" and search for Module (not sure but something like that)
// i need to check again

/*
// some forward declarations
namespace testSfx
{
  void testDll();
  void testSTLalgo();
  void justAtest(Btl::DerivedFromI* aDClass);
  void testBooRsgt1_44_0(); // deprecated ??
  void testPtr2Object();
}

namespace tst
{
  void testClasses();
  void testAdjacentDifference();
  void testRemDel();
  void testAdjacentLimiter();
  void testCharArg(char* aCharstr);
  void maincasTest(); // testing cast stuff (interface)
  void testReconstr(); // scientific algorithm
}

namespace cpp11
{
  void someBindTest();
  void testBindType();
  void testSmartPointer();
  void testMvVector();
  void testBindingFunc();
}

namespace aa
{
  void testBaseCast();
  void testVecAssign();
  void testList();
  void testMap();
  void testCastOperation();
  void testMvList();
  void testRemovingElem();
  //void invertString(char* aStr2Invert);
}

namespace Btl
{
  void testSomeStuff();
  void testProvider();
  void printCombinations(int aNsteps);
  void danAndersonAlgo(const int aNbSteps);
  bool numExists(int array[], int num);
  void testPerformanceMaxMinSum();
  void testInterfaceCastUseCase();
}

// i am not sure about this, why do i have to declare
// in  namespace (equivalent to an extern declaration)
namespace testphy
{
  void testPOM(const std::string& aFilename = "TestResult_5iter.txt");
  void testGblTypes();
}
*/

// create some global variable for managing
// global functionalities of the simulation
testSfx::Global* g_pGlobal = new testSfx::Global;
//Btl::Global* g_btlGlobal = new Btl::Global;

// AlgoritmClass use this global variable in his default ctor
// then since it is not created it crash before initialization
//aa::Global* g_pGlobale=nullptr;  not initialized yet
// problem with that  


// 
struct Line
{
  std::string lineData;

  // implicit cast operator
  operator std::string() const
  {
    return lineData;
  }
};

// operator >> used to read data from stream
// ifstream inherit from istream  
std::istream& operator>> ( std::istream& str, Line& data)
{
  std::getline( str, data.lineData);
  return str;
}

std::pair<double,double> extractCurrency()
{
  return { 1.2, 2. };

}
// int main()
// {
//   std::vector<std::string> lines(std::istream_iterator<Line>(std::cin),
//     std::istream_iterator<Line>());
// }

constexpr int sum( unsigned int n) 
{
  return (n * (n + 1)) / 2;
}

/*
int main(int argc, const char** argv) {
  int var = argc * 4;
  int a = sum(var);              // runtime   

  static_assert(sum(10) == 55); // compile-time
  constexpr auto res = sum(11); // compile-time
  static_assert(res == 66);
  int lookup[sum(4)] = { 0 };   // compile-time
}
*/
bool returnBool()
{
  return true;
}

// Concept
//template <typename T>
//concept Shape = requires( const T & t)
//{
//  { t.area() } -> float;
//};

template <typename T>
struct range_t : private T { // private inheritance
  using T::begin, T::end; /*why this??*/
};

static_assert( std::ranges::range< range_t<std::vector<int>> >);

template <typename T> struct scalar_t { T t{}; /* no begin/end */ };
static_assert(not std::ranges::range< scalar_t<int> >);
// Boost range library
template <class T, class A>
class VectorView : public std::ranges::view_interface<VectorView<T, A>> {
public:
  VectorView() = default;
  VectorView( const std::vector<T, A>& vec) :
    m_begin(std::ranges::next(vec.cbegin(),1)), // similar to boost iterator range "advance_begin(1)" 
    m_end(std::ranges::prev(vec.cend(),-1))     // similar to boost iterator range "advance_end(-1)"
  {}  // .. to be completed
  auto begin() const { return m_begin; }
  auto end() const   { return m_end; }
private:
  typename std::vector<T, A>::const_iterator m_begin{}, m_end{};
};

template<typename ArrayType>
void hllAlgorithm( const ArrayType& aStdVec)
{
  if constexpr ( range_t<ArrayType> rng; std::ranges::range<decltype(rng)>) {
    std::cout << "ArrayType is a range with the following number of elements " << std::ranges::size(aStdVec) <<"\n";
    //std::ranges::size(aStdVec);
    VectorView w_vecView(aStdVec);
  //  std::ranges::sort(w_vecView);
    auto val = w_vecView.back();
    auto begIter = w_vecView.begin();
    auto nbElems = w_vecView.size();
    
    for( const auto& val : w_vecView)
    {
      std::cout << "Value is: " << val << '\n';
    }

    if (w_vecView.begin()!= w_vecView.end())
    {
      std::cout << "Range not empty\n";
    }
  }
}

// struct to test some vector methods
struct structnoCopy
{
  structnoCopy() = delete;
  structnoCopy( int aInt, float aFloat, double aDbl) : m_int{aInt},m_float{aFloat},m_dbl{aDbl} {}
  structnoCopy(const structnoCopy&) {}
  structnoCopy& operator= (const structnoCopy&) { return *this; }

 // structnoCopy( structnoCopy&&) = delete;
  
  int m_int {};
  float m_float {};
  double m_dbl {};
};

// just want to check something (can freely modify the original)
void testRvalueRef( std::vector<int>&& aVec2Chng)
{
  aVec2Chng.push_back(42);
  // do some ting 
  auto aa = aVec2Chng[5] + 2;

  std::cout << "New size of vector is: " << aVec2Chng.size() << "\n";
  std::cout << "Value vector is: " << aa << "\n";
}

// return temporary to initialize variable (Copy Elison is Mandatory since C++117)
// let compiler deduce type (reminder: auto decay!!)
auto getVectorInt() { return std::vector{ 1,2,3,4,5 }; }
auto asStdVector()  { return std::vector{ 1.,2.,3.,4.,5. }; }
auto getBCTpl()     { return std::make_tuple(10., 0.); }

// use Rvalue reference to modify some variable by adding b.c. in the computation phase
// in our programming we impose b.c. by adding a ghost node, but we don't want to modify
// the original which is a scalar field (bind temporary to rvalue reference)
// Usage: TreatmentSource2(w_s, aQ.values().asStdVector(), aA.values().asStdVector(), ...)
//
//  NOTE
//   could use the perfect forwarding (don't need to do that, overload resolution will do)
void TreatmentSource2( std::vector<double>& aS, std::vector<double>&& aQ,  std::vector<double>&& aA,
  double aDx=10., unsigned aNbSections=101)
{
  std::cout << "We are in the Rvalue reference version, we can freely modify the original (avoid copy)\n";

  auto&& [H,Q] = getBCTpl();  // structured binding, universal reference?
  aQ.push_back(std::forward<decltype(H)>(H)); // adding ghost node to the temporary

  // now perform calculation with new added element, for example derivatve at second-order
}
// taking lvalue reference to achieve the same thing, but we need to copy
void TreatmentSource2( std::vector<double>& aS, const std::vector<double>& aQ,  const std::vector<double>& aA,
  double aDx, unsigned aNbSections)
{
  std::cout << "We are in the lvalue reference version, copy to modify the original\n";
  std::vector w_cpyVec{aS};

  // need to apply the b.c. i.e. add  a ghost node
}

// ===================================================================================
//
//                             Window Main Entry Point
//
// ===================================================================================

int sometestmain147( /*int argc, char* argv[]*/)
{
  // since C++17, changes made to char_trait (declare as constexpr) 
  constexpr std::string_view w_strVws{"Msg For Coyote"};

  // since C++17 data() return char*
  std::string w_str{ "dataptr" };
  auto w_strData = w_str.data(); 

  //rvalue reference 
  testRvalueRef( getVectorInt());
  // Universal/forward reference
  auto&& chkVec = getVectorInt();

  std::vector<double> w_S{101}; // initialize to zero
  TreatmentSource2( w_S, asStdVector(), asStdVector()); // pass temporaries (rvalue reference) as args
                                                        // avoid copy and can freely modify original
  std::vector<double> w_A{ 101 }; // initialize to zero
  std::vector<double> w_Q{ 101 }; //  ditto
  TreatmentSource2( w_S, w_Q, w_A, 0.1, 101); // overload resolution const lvalue reference

  //std::make_from_tuple({1.,2.f,3.});
  //structnoCopy ww{};
  structnoCopy w_check{ 1, 2.f, 3. };
  structnoCopy w_check11( std::move(w_check));

 // structnoCopy w_check1(w_check);
  std::vector<structnoCopy> w_testEmplBack;
  // C++17 uses a reference to created object
  //auto& w_refToObj = w_testEmplBack.emplace_back( 1, 2.f, 3.); // forward argument
  w_testEmplBack.push_back({1,2.f,3.});

  // CTAD (Class Template Argument Deduction) feature c++17
  const std::vector w_vecInt{ 4,1,2,5,3,6 };
  auto retIter = std::ranges::begin(w_vecInt);
  VectorView w_vecView(w_vecInt);
  auto val = w_vecView.back();
  hllAlgorithm(w_vecInt);

  // testing view
  //VectorView<int> myView(w_vecInt);
  //std::views::istream_view<int>(std::cin);

 /* if constexpr( range_t<std::vector<int>> r; std::ranges::range<decltype(r)>) {
    std::cout << "r is a range\n";
  }*/

  using namespace std::literals;
  auto w_str1 { "24321"s };
  std::string w_str2{ "21321" };
  // spaceship operator
  auto isEqual = w_str1 <=> w_str2; 

  // C++ 17 feature if
  if( bool myBool = returnBool())
  {
    std::cout << "Check compile time if\n";
    std::cout << "Value is: " << myBool << "\n";
  }

  //constexpr function can be static assert
  static_assert(sum(10) == 55); // compile-time
  constexpr auto res = sum(11); // compile-time

  //constexpr std::vector<int> myCexprV(5,2);

  // std::ranges algorithm C++20 (new features)
  //std::ranges::sort(w_vecInt);
 
  //auto rng2 = std::ranges::unique(rng1);
  // new features of C++17, temlate argument deduction
  // here int is implicitly deducted
  using namespace std::literals;
  constexpr auto myStrView =  // 'char_trait' has changed in C++20
    R"(F:\TestVS19\JeanSlnVS19\DamBreakSimulator\ParamOfRun.txt)"sv;
 
	std::cout << "VS19 test 14/17 C++ features\n";

  const auto w_checkVal = "asdsadsa"s;
  if (w_checkVal.starts_with("asd"))
  {
    std::cout << "C++20 string feature supported\n";
  }

  // R"(F:\TestVS19\JeanSlnVS19\DamBreakSimulator\ParamOfRun.txt)"
  // raw string feature (csv file)
  std::ifstream w_ifStream( myStrView.data());
  
  if( w_ifStream.is_open()) { // open for reading
    std::vector<std::string> w_vecStr;
    w_vecStr.reserve(10);
   
    // iterator from a stream (copy each line of file in vector)
    std::copy( std::istream_iterator<Line>(w_ifStream), //begin range
      std::istream_iterator<Line>(), // end range
      std::back_inserter(w_vecStr)); // store lines in vector

    // count number of bill in a file ("signature")
//     auto w_countSignature = 0; // type deduction is integer
//     auto w_numofBill = std::count_if( std::istream_iterator<Line>(w_ifStream), //begin range
//       std::istream_iterator<Line>(), 
//       [&w_countSignature] ( const Line& aLine)
//       {
//         // check for "signature" token for each line (return iterator pos of keyword)
//         // could use to split our whole file into separate bill 
//         auto w_pos = std::search( aLine.lineData.cbegin(), aLine.lineData.cend(), std::string("signature"));
//         if (w_pos!=aLine.lineData.cend())
//         {
//           ++w_countSignature;
//         }
//       });

//    std::cout << "we have " << w_countSignature << " in this file \n";
    // could check for transporteur name with any_of
    //std::any_of();

    w_ifStream.close(); // close file finis reading
  }

  if (nullptr!=g_pGlobal)
  {
    delete g_pGlobal;
    g_pGlobal = nullptr;
  }

	return EXIT_SUCCESS;
}