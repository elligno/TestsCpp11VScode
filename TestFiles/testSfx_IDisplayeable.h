#pragma once

// C++ include
#include <iostream>

namespace testSfx
{
	/** 
	 * This interface provide the service to display something.
	 * Again to be used in callback mechanism.
	 */
	class IDisplayeable 
	{
	public:
		/** 
		 * A pure virtual member.
		 */
		virtual void display()=0;
	protected:
		/** 
		 * destructor (shall be virtual)
		 */
		~IDisplayeable() {std::cout << "We are in IDisplayeable dtor\n";}
	};
} // End of namespace