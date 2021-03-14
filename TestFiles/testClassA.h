#pragma once

// C++ include
#include <iostream>

namespace tst {class AA;}

/** @namespace Tst
 * This namespace is a test.
 */
namespace tst
{
	/**
	 * We are testing the mathematical documentation using Latex
	 * as part of doxygen (Miktex, dvips and ghostscript).
	 * Math formula are included in the documentation as the following 
	 * The equation that we are solving is \f$U_t + L = S\f$ where
	 * - Equation term are the following
	 *   - U is the state variable
	 *   - L is the differential operator (spatial term)
	 *   - source term (bottom and friction)
	 *   .  
	 */


	/**
	 * @brief We are testing the mathematical documentation using Latex
	 * as part of doxygen (Miktex, dvips and ghostscript).
	 * 
	 */
	class A
	{
    // C++11 enumeration (scoped enumeration)
    enum class eTypeImpl: char
    { 
      high='h',
      low='l', // C++11 allows the extra comma
    }; 
	public:
     /** 
		 * default ctor.
		 */
		A();
		/** 
		 * An explicit ctor (doesn't allowed the implicit conversion).
		 * @param aI an integer (conversion).
		 */
		explicit A( int aI);    
		/** 
		 * implicit conversion not allowed.
		 * @param aI an integer.
		 * @param aPtr a pointer to an int.
		 */
		A( int aI, int* aPtr);  
		/*  * 
		 * virtual destructor.
		 */
		virtual ~A();  
		/** 
		 * compiler copy and assignment ctor shall be fine.
		 * actually as a soon as we have a pointer as an attribute.
		 * we shall define the copy and the assignment ctor.
		 */
		A( const A& aOther);
    /** 
		 * compiler copy and assignment ctor shall be fine.
		 */
    A( int aI, unsigned  aSize, int* aPtr)
    : m_iPtr(aI),
      m_name("TestCtor"),
      m_ptr(nullptr),
      m_ptrSize(aSize)
    {
      // just allowed some memory (should allocate try/catch in a ctor?)
      // i am not sure about this last one
    }
    A& operator= ( const A& aOther);

		/** 
		  Public methods of the base class, inherited by derived class.
		 */
		int   getI()   const { return m_iPtr+=1;}
    
    // two version of the same method (read/write)
		int*  getPtr() const { return m_ptr;}
		int*& getPtr()       { return m_ptr;}
     
    // some static function
		static int testStatic() 
		{
			int w_var = m_st+1;
			return m_st;
		}

		// can be overriden by subclass
		virtual void print() 
    { 
      std::cout << "We are in A::print() method\n";
    }
		
    void callImpl();
    /** 
		 * just a test method.
		 * @param aChar a character that is not used.
		 */
		int test( const char aChar) 
		{ 
			std::cout << "We are in A::test()\n";
      if (aChar!='a')
      {
        std::cout << "this char is not equal to a\n";
      }
			return 0;
		}
		
    /** 
		 * @result 
		 */
		const std::string& name() const {return m_name;}
  protected:
    // these can be overriden by subclass
    virtual void anImpl() { std::cout << "an impl of A\n";     }
    void anotherImpl()    { std::cout << "another impl of A\n";}
	private:
		static int m_st;      // need to be initialized when used 
		size_t m_ptrSize;     // number of data elements
		mutable int m_iPtr;   // return by the getI() method
		int* m_ptr;           // hold the data
		std::string m_name;   // string rep of the class
    AA* m_aaFwrd;         // just an implementation 
    eTypeImpl m_implType; // ...
    void Copy();          // initialize data helper 
  };
} // End of namespace