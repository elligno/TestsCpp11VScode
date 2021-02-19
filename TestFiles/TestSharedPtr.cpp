
#include <cassert>
#include <iostream>
#include <fstream>
#include <memory>   // shared_ptr + cast operator 
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
		shared_ptr<int> w_testShPtr = make_shared<int>();
		shared_ptr<int> w_px(new int);
        int w_testVal=*w_testShPtr;    // 0
		int w_valx=*w_px;              // some weird value
		
		// check count of the smart pointer
		size_t w_checkCount = w_testShPtr.use_count();
		assert( w_testShPtr.use_count()==1); // at creation

		// set some initial values
		int* w_intPtr=w_testShPtr.get();  // pointer
		assert( w_intPtr != nullptr);
		int w_checkPtr = *w_testShPtr;
		assert(w_checkPtr==0);
		w_checkPtr=2; // it change the shared ptr value??
		              // no, don't see why it should!!

		// change it but with pointer
	    assert(*w_testShPtr==0);
		*w_intPtr=45; // changing smart pointer (object) value
		assert(*w_testShPtr.get()==45);

		//	assert(w_checkPtr!=nullptr);
		// allocate memory to store 5 values (int) 
		int* w_ptrArr = new int[5];
		int* w_tmptr=w_ptrArr;
		*w_ptrArr++=1;
		*w_ptrArr++=2;
		*w_ptrArr++=3;
		*w_ptrArr++=4;
		*w_ptrArr=5;
		// reset to begin 
		w_ptrArr-=4; 
		assert( w_ptrArr==w_tmptr);

		// i think we should do a reset instead
		// this operation is dangerous 
		// actually we just re-assign the pointer, 
		// it doesn't affect the shared pointer at all
		w_intPtr = w_ptrArr; // set to new value, that's it!!
		// some check
		int* w_intPtr1=w_testShPtr.get();  // pointer (still the same pointer!!)
		int w_newVal1=*w_intPtr1;
		assert(w_newVal1==45);   // same value!!
		// copy ctor!!
		std::shared_ptr<int> w_cpyPtr=w_testShPtr;
		assert(w_testShPtr.use_count()==2);
		assert(w_cpyPtr.use_count()==2); // it's copy, must have same value
		int w_cpyVal = *w_cpyPtr; // int value
		assert(w_cpyVal==45);
        *w_cpyPtr=23; // changing copy object
		assert(*w_testShPtr==23); // ?? it is? 
		// yes it is and it make sense. Smart ptr are handle that ref
		// count on ptr. When i do a copy behind the hood i'm changing
		// pointer value both pointer point to same location!!
		w_testShPtr=w_cpyPtr; // assignment ctor (must be same for assignment)
		*w_testShPtr=12;
		assert(*w_cpyPtr==12);

		// check reset stuff
		int* w_newInt = new int;
		int* w_tmpSptr=w_testShPtr.get();
		w_testShPtr.reset( w_newInt);
		int* w_getPtr=w_testShPtr.get();
		assert( w_tmpSptr != w_getPtr);
		assert(*w_getPtr!=0); // new value, since we have reseted the smart pointer
		
		std::cout << "We are leaving the TestSharPtr function\n";
	}

  // Should never
  // // do i transfer ownership when passing 
  void passUniquePtr( std::unique_ptr<int> aUniquePtr)
  {
    std::cout << "Pass unique ptr as argument\n";
    int* w_ptr2int = aUniquePtr.get();
    assert(*w_ptr2int==1234);
  }

  void unique2Ptr(int* aPtr2Int)
  {
  }

	// smart pointer with user defined type
	void testuniquePointer()
	{
		using namespace std;

    // create a unique ptr
    unique_ptr<int> w_testUniqueptr;

    // can i test the unique ptr against nullptr? yeap
    if( nullptr==w_testUniqueptr)
    {
      cout << "Can test the unique ptr on nullptr\n";
      w_testUniqueptr.reset(new int);
      assert(w_testUniqueptr!=nullptr);
    }
    if( !w_testUniqueptr)
    {
      cout << "Can test on overload operator!\n";
    }

    // assigning a value to the object or pointee.
    // Problem we a null pointer
    *w_testUniqueptr = 1234;

    // can pass it as a variable, because you cannot transfer 
    // ownership the only way to do that is to use the move
    // semantic.
    // In the case of auto_ptr which is deprecated, you can pass it
    // directly and it transfer ownership. But ting s are different 
    // with unique pointer. One must use the move semantic to transfer ownership.
    passUniquePtr( std::move( w_testUniqueptr));
    
    // by using move semantic you transfer ownership
    if( w_testUniqueptr==nullptr)
    {
      cout << "Transfered ownership successfully\n";
    }
    // create another unique ptr, again cannot use copy ctor without using
    // move semantic, ensure that the transfer of ownership is done
    unique_ptr<int> w_another = std::move( w_testUniqueptr);
    if( w_another==w_testUniqueptr)
    {
      cout << "These 2 unique ptr are equal\n";
    }

    // cannot convert to dumb pointer
   // unique2Ptr( std::move(w_testUniqueptr));

    cout << "Just tested the ownership transfer\n";

    std::ifstream w_checkOpening("MyData.txt");
    // overload operator void* i guess (implicit conversion)
    if (w_checkOpening)
    {
      cout << "Checked opening on this file\n";
    }
	}
} // End of namespace