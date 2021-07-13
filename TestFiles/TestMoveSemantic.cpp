
// C++ include
#include <memory> // unique pointer
#include <iostream>
#include <string>
#include <tuple>
#include <list>
// Boost includes
#include <boost/noncopyable.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/assign/std/vector.hpp>
// App include
#include "../Classes/myMoveClass.h"

// Reference: see article "C++11 feature that every programmer should know ..."
// Also see reference appendix book of Anthony Wilson "Concurrency ..."
// Finally Thomas Becker article about this topic.
// Move semantic is a copy by moving pointer (removing) re-assign pointer 

namespace cpp11 
{
  // right-value reference (move semantic)
  void moveFunc( std::vector<int>&& aMv) // rvalue as argument
  {
    // IMPORTANT inside the function aMv is a left value
    // looks like it's working (i am not sure the behavior)
    std::vector<int> w_checkMv( std::move(aMv)); // call move ctor

    // do we still have a vector after this operation
    // let's check  if we still have a vector that it's working
    if( aMv.empty())
    {
      std::cout << "I still do understand the move semantic\n";
    }
  }

  // what for?
  // check list if it still have pointer
  //aa::inheritSomeClass* = static_cast<aa::inheritSomeClass*>(w_checkCast.front());
//   std::list<aa::inheritSomeClass*> w_listOfderived;
//   const std::string& w_byref =  std::string("jean ");

//  aa::inheritSomeClass w_checkCopy(const_cast<std::string&>(w_byref));
  //  w_listOfderived.push_back(aa::inheritSomeClass());

  void testMvVector()
  {
    using namespace boost::assign;

    // Testing move ctor of the std::vector
    std::vector<int> w_orgVec;
    w_orgVec += 1,2,3,4,5;

    // using the move semantic (original vector shall be empty after this operation)
    std::vector<int> w_mvVec = std::move(w_orgVec);

    // sanity check (move semantic the original vector shall be empty) 
    if( w_orgVec.empty())
    {
      std::cout << "I do understand the move semantic basically\n";
    }

    // we try to bound a right value reference to a left value
    //moveFunc(w_mvVec); compile error, trying to bound a lvalue to a rvalue
    moveFunc( std::move(w_mvVec)); // now it works
    
    // looks like it's working, do create a temporary object? NO!!!
    moveFunc( std::vector<int>(5)); // 5 element initialized to zero

    // create a ove 
    std::vector<vs15::MoveTest> w_mvTestVec;
  }

  // rvalue reference
  void testMyMvCtor( vs15::MoveTest&& aMvObj)
  {
    // IMPORTANT 
    //   Although rvalue reference can bind to rvalue, within
    //   a function itself it is treated as an lvalue.   
    std::cout << "We have a mv ctor working\n";
    vs15::MoveTest w_mvClass;
    vs15::MoveTest w_mv2Cpy = w_mvClass; // copy ctor?
  }

  vs15::MoveTest checkSomeNvFeatures()
  {
    vs15::MoveTest w_mvClazz( std::string("JeanMvTest"));
    w_mvClazz.addElem(1);
    w_mvClazz.addElem(2);
    w_mvClazz.addElem(3);

    return w_mvClazz; // return by value means temporary object (call mv ctor)
  }

  void testRefSemantic()
  {
    std::cout << "Testing the reference semantic\n";
    // creating a vector of smart pointer
    std::vector<std::unique_ptr<vs15::MoveTest>> w_refSemantic;
   
    // just testing, this way make things clear instead of using number
    // each enumerator variable has its corresponding variables in tuple 
    // tuple variables (use with get)
    enum TplVar 
    {
      A=0,
      Q=1,
      H=2
    };

    // Scott Meyers comment about the only reason why we should use old enum 
    std::tuple<double, double, double> w_typeDeuc = std::make_tuple(1.,2.,3.);
    auto w_A = std::get<TplVar::A>(w_typeDeuc); // Wetted area

    std::cout << "Tuple first value is: " << w_A << std::endl;
  }
} // End of namespace