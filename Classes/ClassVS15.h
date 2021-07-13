
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

		// copy/move deleted (copy elison test)
		Classvs15( const Classvs15& aOther);
		Classvs15( Classvs15&& aOther);
	protected:
		void initialize() { throw "not implemented yet";}
	private:
		int m_y; 
		std::vector<int*> m_vec;
		std::string m_name;
	};
} // End of namespace
