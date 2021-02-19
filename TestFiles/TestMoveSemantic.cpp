
// C++ include
#include <memory> // unique pointer
#include <iostream>
#include <string>
#include <list>
// Boost includes
#include <boost/noncopyable.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/assign/std/vector.hpp>

// test 
// temporary fix
namespace aa {class inheritSomeClass;} // ??

// Reference: see article "C++11 feature that every programmer should know ..."
// Also see reference appendix book of Anthony Wilson "Concurrency ..."
// Finally Thomas Becker article about this topic.
// Move semantic is a copy by moving pointer (removing) re-assign pointer 

namespace cpp11 
{
  class MoveTest
  {
  public:
    // testing ctor 
    // default ctor
    MoveTest() { std::cout << "Default ctor of MoveTest\n";}
    MoveTest( const std::string& aStr) : m_str11(aStr) {}
    // Copy ctor
    MoveTest( const MoveTest& aOther) { std::cout << "Copy ctor of MoveTest\n";}
    // Move ctor
    MoveTest( const MoveTest&& aOther) { std::cout << "Move ctor of MoveTest\n";}
  protected:
  private:
    std::string m_str11;
    std::vector<int> m_vecofInt;
  };

  // right-value reference (move semantic)
  void moveFunc( const std::vector<int>&& aMv)
  {
    // looks like it's working (i am not sure the behavior)
    std::vector<int> w_checkMv = aMv;

    // do we still have a vector after this operation
    // let's check  if we still have a vector that it's working
    if (aMv.empty())
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
    if (w_orgVec.empty())
    {
      std::cout << "I do understand the move semantic basically\n";
    }

    // we try to bound a right value reference to a left value
    //moveFunc(w_mvVec); compile error, trying to bound a lvalue to a rvalue
    moveFunc( std::move(w_mvVec)); // now it works
    
    // looks like it's working, do create a temporary object?
    moveFunc( std::vector<int>(5)); // 5 element initialized to zero

    // create a ove 
    std::vector<MoveTest> w_mvTestVec;
  }

  void testMyMvCtor( const MoveTest&& aMvObj)
  {
    using namespace boost::assign;

    std::list<int> w_listInt;
    w_listInt = list_of(1)(2)(3)(4)(5);

    std::cout << "We have a mv ctor working\n";
  }

  void testRefSemantic()
  {
    std::cout << "Testing the reference semantic\n";
    // creating a vector of smart pointer
    std::vector<std::unique_ptr<MoveTest>> w_refSemantic;

  }
} // End of namespace