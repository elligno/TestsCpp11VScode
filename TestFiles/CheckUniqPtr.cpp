
#include <cassert>
#include <iostream>
#include <memory>

namespace vs11 
{
    // move semantic
    void someUniqPtr(std::unique_ptr<int> aX)
    {
        *aX = 4;
    }
    // testing some unique pointer functionalities
    void checkUniqPtr()
    {
        auto w_valFromUniq = std::make_unique<int>(3);
        someUniqPtr( std::move(w_valFromUniq));                      // move semantic make "w_valFromUniq" in undefined state (look in dbg variable)
        std::cout << "Pointer value is: " << *w_valFromUniq << "\n"; // actually print garbage, because it doesn't make sense
                                                                     // by def of move semantic, move steal the content of it
    }

    // Should never
  // do i transfer ownership when passing 
  void passUniquePtr( std::unique_ptr<int> aUniquePtr)
  {
    std::cout << "Pass unique ptr as argument\n";
    int* w_ptr2int = aUniquePtr.get();
    assert(*w_ptr2int==1234);
  }

  // smart pointer with user defined type
  void testuniquePointer()
  {
 	using namespace std;

    // create a unique ptr (init to nullptr)
    unique_ptr<int> w_testUniqueptr(nullptr);

    // can I test the unique ptr against nullptr? yeap
    if( nullptr == w_testUniqueptr)
    {
      cout << "Can test the unique ptr on nullptr\n";
      w_testUniqueptr.reset(new int{}); // should initialize to some def values (0)
      assert( nullptr != w_testUniqueptr);
    }

    if( !w_testUniqueptr)
    {
      cout << "Can test on overload operator!\n";
      // int value should be garbage, not initialized with def ctor
      cout << "unique ptr value is: " << *w_testUniqueptr << "\n";
    }

    // assigning a value to the object or pointee.
    // Problem we a null pointer
    *w_testUniqueptr = 1234;

    // can pass it as a variable, because you cannot transfer 
    // ownership the only way to do that is to use the move
    // semantic.
    // In the case of auto_ptr which is deprecated, you can pass it
    // directly and it transfer ownership. But things are different 
    // with unique pointer. One must use the move semantic to transfer ownership.
    passUniquePtr( std::move( w_testUniqueptr));
    
    // by using move semantic you transfer ownership
    if( nullptr == w_testUniqueptr) // not if it is left in a nullptr 
    {
      cout << "Transfered ownership successfully\n";
    }

    // create another unique ptr, again cannot use copy ctor without using
    // move semantic, ensure that the transfer of ownership is done
    unique_ptr<int> w_another = std::move( w_testUniqueptr);
    if( w_another == w_testUniqueptr)
    {
      cout << "These 2 unique ptr are equal\n";
    }

    // cannot convert to dumb pointer
   // unique2Ptr( std::move(w_testUniqueptr));

 //   cout << "Just tested the ownership transfer\n";

 }

 // Could be use in our numerical library with legacy code 
 // for finitie difference derivative. 
 std::unique_ptr<int []> retUniquePtrArray(/*stencil* aDfDsten*/)
 {
     // some test with array (operator [] is defined)
     // call delete [] when it go out of scope
     std::unique_ptr<int []> w_uniqArr( new int[5]); 
     // initialize the array
     w_uniqArr[0]=0;
     w_uniqArr[1]=1;
     w_uniqArr[2]=2;
     w_uniqArr[3]=3;
     w_uniqArr[4]=5;

     // transfer the ownership (call std::move implicitly) 
     return w_uniqArr;
 }
} // End of namespace