
#pragma once

// C++ includes
#include <memory>
#include <iostream>
// stl include
#include <vector>

namespace vs15 
{
	class Classvs15 
	{
	public:
		// default ctor (no implicit conversion)
		explicit Classvs15( int y = 10);
		virtual void print() { throw "not implemented yet";}
	protected:
		void initialize() { throw "not implemented yet";}
	private:
		int m_y;
		std::vector<int*> m_vec;
	};
} // End of namespace
