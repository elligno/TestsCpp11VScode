
#include <cassert>
#include <iostream>
#include <fstream>
#include <memory>   // shared_ptr + cast operator 
#include <string>
// declare some classes for testing purose
#include "TestClassesUtil.h"

// Some new cast operator are introduced in C++11 for casting
// shared pointer from derived to base and vice versa
// These are the following:
// std::static_pointer_cast
// std::dynamic_pointer_cast
// std::const_pointer_cast
//  
//  Used with shared pointer  (http://en.cppreference.com/w/cpp/memory/shared_ptr/pointer_cast)
//  
namespace cpp11 
{
  // similar to the StateVector in our programming env.
	// actually it's just a pair of smart pointer
	// under construction!!!
	struct testpairshr 
	{
		typedef std::shared_ptr<TestShrPtr> shrptr2type;
		std::pair<shrptr2type,shrptr2type> m_pairint;

		// some method!! 
		shrptr2type getFirst() const  { return m_pairint.first; }
		shrptr2type getSecond() const { return m_pairint.second;}
	};

	// Some test about the std shared pointer
	void testSmartPointer()
	{
		using namespace std;

		// create a boost smart pointer (call default ctor of int, 
		// set init value to 0). Better to use the make_shared utility
		// than ... for this reason make sure object is constructed 
		// (need more test) and it's faster
		// it seems that the make_shared call default ctor to ensure
		// that type is constructed completely, not sure but looks like it!! 
		shared_ptr<int> w_testShPtr = make_shared<int>(); // init to zero?
		shared_ptr<int> w_px(new int{}); // init to zero (add parenthese)
        int w_testVal = *w_testShPtr;    // 0
		int w_valx = *w_px;              // some weird value (probably garbage) now should be zero
		
		// check count of the smart pointer
		size_t w_checkCount = w_testShPtr.use_count();
		assert( w_testShPtr.use_count() == 1); // at creation

		// set some initial values
		int* w_intPtr = w_testShPtr.get();  // pointer
		assert( w_intPtr != nullptr);
		int w_checkPtr = *w_testShPtr;
		assert(w_checkPtr == 0);
		w_checkPtr = 2; // it change the shared ptr value??
		              // no, don't see why it should!!

		// change it but with pointer
	    assert(*w_testShPtr == 0);
		*w_intPtr=45; // changing smart pointer (object) value
		assert(*w_testShPtr.get() == 45);

		//	assert(w_checkPtr!=nullptr);
		// allocate memory to store 5 values (int) 
		int* w_ptrArr = new int[5];
		int* w_tmptr = w_ptrArr;
		*w_ptrArr++ = 1;
		*w_ptrArr++ = 2;
		*w_ptrArr++ = 3;
		*w_ptrArr++ = 4;
		*w_ptrArr = 5;
		// reset to begin 
		w_ptrArr -= 4; 
		assert( w_ptrArr == w_tmptr);

		// i think we should do a reset instead
		// this operation is dangerous 
		// actually we just re-assign the pointer, 
		// it doesn't affect the shared pointer at all
		w_intPtr = w_ptrArr; // set to new value, that's it!!
		// some check
		int* w_intPtr1 = w_testShPtr.get();  // pointer (still the same pointer!!)
		int w_newVal1 = *w_intPtr1;
		assert(w_newVal1 == 45);   // same value!!
		// copy ctor!!
		std::shared_ptr<int> w_cpyPtr = w_testShPtr;
		assert(w_testShPtr.use_count() == 2);
		assert(w_cpyPtr.use_count()==2); // it's copy, must have same value
		int w_cpyVal = *w_cpyPtr; // int value
		assert(w_cpyVal == 45);
        *w_cpyPtr=23; // changing copy object
		assert(*w_testShPtr == 23); // ?? it is? 
		// yes it is and it make sense. Smart ptr are handle that ref
		// count on ptr. When i do a copy behind the hood i'm changing
		// pointer value both pointer point to same location!!
		w_testShPtr = w_cpyPtr; // assignment ctor (must be same for assignment)
		*w_testShPtr = 12;
		assert(*w_cpyPtr == 12);

		// check reset stuff
		int* w_newInt = new int{};
		int* w_tmpSptr=w_testShPtr.get();
		w_testShPtr.reset( w_newInt);
		int* w_getPtr = w_testShPtr.get();
		assert( w_tmpSptr != w_getPtr);
		assert(*w_getPtr != 0); // new value, since we have reseted the smart pointer
		
		std::cout << "We are leaving the TestSharPtr function\n";
	}

   // good question, what do i think
  void someSharedPtr( std::shared_ptr<int> aX)
  {
    // what do we do here? pointed-to
    auto w_ptd2Auto = *aX;

    // this is the pointer owned by the shared pointer 
    auto* w_ptrFromShrd = aX.get();
    
    // re-use of auto type
    decltype(w_ptd2Auto) w_var = 2;
   
    std::cout << "Type of shared ptr is: " << typeid(w_ptd2Auto).name() << "\n";

    *aX = 3; // modofy the object
  }

  void someSharedPtrRef( std::shared_ptr<int>& aX)
  {
	  // ref count not incremeneted (pass by ref)
    auto checkCount = aX.use_count();
    *aX = 3; 
  }

  void checkShrPtr()
  {
    auto w_valFromShr = std::make_shared<int>(65);
    someSharedPtr( w_valFromShr); // still 65 because work on copy (pass-by-value) NO!!! modify pointed-to
    std::cout << "Pointer value is : " << *w_valFromShr << "\n";

    // count when pass by ref? increment it? no because not copy
    auto w_valFromShrRef = std::make_shared<int>(5);
    someSharedPtrRef( w_valFromShr); // 
    std::cout << "Pointer value is : " << *w_valFromShr << "\n";
  }

  void shrPtr4Array()
  {
	  // create a shared pointer string (use direct list initialization {})
	  // deleter pass as ctor argument (second)
	  std::shared_ptr<std::string> w_ptr2Str { new std::string {"Jean"},
	  [] ( std::string* aStr ) // defining own deleter (coulld have use std::default_delete<std::string>)
	  {
		  std::cout << "delete " << *aStr << std::endl; 
		  delete aStr;
	  }}; 

      // Provide a deleter for array new [] operator, because shared_ptr will call delete
	  // error at run time  
	  std::shared_ptr<int> p { new int[5] }; // ERROR, but compiles (call delete not delete [])

      std::shared_ptr<int> w_shr2IntArr { new int[5], // must provide deleter
	  [] ( int* aPtr2Arr) // own deleter for array  NOTE: C++17 it is supported 
	  {
		  delete [] aPtr2Arr;
	  }
	  };

	  // In C++11 and C++14 it is valid to construct a std::shared_ptr<T> from a std::unique_ptr<T[]>:
	  // Since the shared_ptr obtains its deleter (a std::default_delete<T[]> object) from the unique_ptr, 
	  // the array will be correctly deallocated. Can we access element with operator []?
      std::unique_ptr<int[]> arr( new int[1]);
	  arr[0] = 1; // use in the derivative library (finite difference) 
      std::shared_ptr<int> ptr( std::move(arr));
	  // ptr[0]=2; not syupoported before C++17
  }
} // End of namespace