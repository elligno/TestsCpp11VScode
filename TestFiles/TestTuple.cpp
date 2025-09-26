#include <cassert>
#include <iostream>
// C++11 includes
#include <optional>
#include <string>
#include <tuple>
// stl include
#include <vector>
// some testing for our new Nodal_Value
#include "../Testcpp20/SomeConcepts.hpp"

namespace {
  struct Nodal_Value  // experimenting some basic concepts 
  {                   // return to the basic and make things simpler
    using tpl3 = std::tuple<int/*id*/, double/*value*/, double/*value*/>;
    // function to test some new utility for tuple-like
    Nodal_Value( int aId, double aVal1, std::optional<double> aVal2=std::nullopt)
    : m_tpl3{aId, aVal1, aVal2.value()} // need to check Nico's book about calling value
    {
      std::cout << "Calling our func 3 args from tuple utility\n";
    }
    Nodal_Value( std::tuple<int, double,double> aTplValues)
    : m_tpl3{std::move(aTplValues)}
    {}

    // copy, assignemnt ctor and move copy, assignment are automatically genereated

    tpl3 values() {return m_tpl3;}

    // return the number of element (don't make sense!!)
    std::size_t getSize() const {return std::tuple_size<tpl3>();}

    void print() {
      using namespace cpp20;
      std::cout << m_tpl3; // use the operator << defined in SomeConcepts (std::apply)
      }

    tpl3 m_tpl3;

    // this could be the NodalValue?
    template<typename ...Params>
    struct myTplArgs
    {
      std::tuple<Params...> data;
    };
    
  }; // Nodal_Value

  struct GeoNode : Nodal_Value
  {
    GeoNode(int aId, double aXcoord)
    : Nodal_Value{aId,aXcoord} {}
    /* data */
  };
  
  class Uh
  {
  private:
    /* data */
  public:
    Uh(/* args */);
    ~Uh();
  };
  
  Uh::Uh(/* args */)
  {
  }
  
  Uh::~Uh()
  {
  }
  
}
namespace cpp20
{
   // testing tuple of cpp11
  void testTupleCpp11()
  {
    using  tuple_t = std::tuple<double,unsigned,std::string>;
    tuple_t w_tupleCpp = std::make_tuple(2.,1,std::string("tuple"));
    std::cout << "we are testing tuple\n"; 

    auto tpl3 = std::make_tuple(1,0.2,23.45);
    auto tmpTpl = std::make_tuple(2,0.2,2.5);
    std::vector<Nodal_Value> myVecOfTpl;  // Uh class that use to be too complicted for our need
    myVecOfTpl.reserve(3);  // just for testitng
    myVecOfTpl.push_back( std::make_from_tuple<Nodal_Value>(std::move(tpl3))); //rvalue
    myVecOfTpl.push_back( std::make_from_tuple<Nodal_Value>(std::tuple{1,1.3,45.2})); //ditto
    myVecOfTpl.push_back( std::make_from_tuple<Nodal_Value>(std::make_tuple(2,0.2,2.5))); //ditto
    assert(3 == myVecOfTpl.size());
    // basic test (reminder auto decay, strip reference and const qualifier)
    const auto& firstTpl =  myVecOfTpl.front();  // shall return a reference
		auto[id,A,Q] = myVecOfTpl.front().values();  // structured binding

    // Can i copy? and even mode

    // Can we copy tuple? why not!
    // what about stuctured binding C++17? is it working?

		//std::cout << "This is our new created tuple: " << w_tupleCpp << "\n"; 
  }
} // End of namespace