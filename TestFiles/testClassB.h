#pragma once

// App. include
#include "testClassA.h"
#include "testSfx_IUpdateable.h"
#include "testSfx_IDisplayeable.h"

/** @namespace tst
 * The namespace tst contains classes and interface.
 * to be tested. We are testing the doxygen documentation.
 * tool that we plan to use in our development environment. 
 */
namespace tst
{
	/** 
	 * Derived class from the base class and 2 interface.
	 * Use the keyword virtual when inheriting from interface. 
	 * because of the method duplication (not sure, to be confirmed).
	 */
	class B : public A, 
		        public virtual testSfx::IUpdateable,
		        public virtual testSfx::IDisplayeable 
	{
	public:
		B() : A()  { std::cout << "We are in B default ctor\n";}
	//	B(A aA) {} for implicit conversion
		~B() { std::cout << "We are in class B dtor\n";  }

		// overriden from A
		void print() override { std::cout << "We are in B::print() method\n";}
		// B methods (overloading the print method (not the same signature))
		void print( std::ostream& aStream) { aStream << "B::print(std::ostream) method\n";}
		/** 
		 * Just a test function, 
		 * @param aChar a character (not used)
		 * @result return an integer
		 */
		int test( char aChar) 
		{
			std::cout << "We are in B::test()\n";
			return 1;
		}

		/** 
		 * Methods inherited from the interface.
		 * The update method is implemented if you want.
		 * to update something. The display method is.
		 * implemented by someone who want to display something.
		 */
		void update()  override { std::cout << "We are in B::update()\n";}
		void display() final override { std::cout << "We are in B::Display()\n";}
	};
} // End of namespace