
//  Author: Jean Belanger (Elligno Inc.)
//  Date of creation: december 21, 2015
//  

#include <cassert>
// C++ includes
#include <string>
#include <iostream>
// STL includes
#include <vector>
#include <functional> // std::function ?
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

namespace cpp11 
{
  //typedef void (*p2f)(double, int);  usage: p2f myptr2func;
  using ptrf = void (*)(double, int); // c++11 way 
  // can i do that? actually can i assign to a pointer-to-function
  // myBinFunc wTestStdFunc=myptr2func; ?? can i?
  
  // std::function is a kind of delegate similar to C# delegate
 ptrf mybinFunc; //= std::function<void (double,int)>;

  // some function 
  void testFunc( double aDbl, int aInt) {std::cout << "Test ptr-2-func\n";}
  void compute_rhs( double aDbl, int aInt) {}

  //
  // TODO: remember to do something with this function
  template <class C /*container*/, class T/**/> class Integrator
  {
  protected:
    C statevector;
    T t, h; // time and time step
    void (*return_derivs)( const C&, const T, C&);

    Integrator ( const C&, const T, const T,
      void (*)( const C&, const T, C&)); // ptr-2-func

  public:
    // Virtual destructor allows deletion of derived objects
    virtual ~Integrator() { }

    // Every integrator must have a step() function which
    // updates the state.
    virtual void step() = 0;

    // Function to retrieve the current time
    T current_time() const {return(t);}

    // Function to retrieve the current state of the system
    void get_state(C&, T&) const;

    // Function to (re)set h
    virtual void set_step_size(T new_h) {h = new_h;}
  };

  // want to test the std function and compare with ptr-2-function
  // function  is a delegate very similar to c# delegate (oriented 
  // version of the pointer-2-function)
  void createptr2func(ptrf aPtr2Func)
  {
    // can we check if a pointer to func is null?
    // whatever
  }
  // not sure what u want to do?
  void ptr2FuncEntryPoint()
  {
    // ...
  }

  // TODO: this test need to be completed
  void testBindAndFunc()
  {
    // Testing the bind mechanism
    using namespace std::placeholders;
    auto myFunc = std::bind( std::plus<double>(),_1,2.3);

    // shall print 4.5
    std::cout << "myFunc adding result is: " << myFunc(1.2) << "\n";
    // create a delegate or std::function
    std::function<double(double)> w_stdFun = std::bind( std::plus<double>(),_1,2.3);
    std::function<void(double,int)> w_ptr2func = testFunc;
    w_ptr2func(1.2,2);
    auto w_checkPtrFunc = std::bind(testFunc,0.23,_2);
  }
} // End of namespace