#pragma once

// C++ include
#include <iostream>
#include <string>

namespace Btl 
{
	//
	// Multiple inheritance through interface
	//
	class IAnotherInterface 
	{
	public:
		virtual const std::string& toString() const=0;

		// add a virtual destructor
		virtual ~IAnotherInterface() 
		{ std::cout << "We are in IAnotherInterface dtor\n";}
	};
} // End of namespace 