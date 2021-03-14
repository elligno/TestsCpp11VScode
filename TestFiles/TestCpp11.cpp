// C++ includes
#include <iostream>
#include <array>
#include <vector>
// Boost include
#include <boost/range/iterator_range.hpp> // iterator range library

// namespace 
// {
// 	constexpr auto arraySize2 = 10; // fine, 10 is a 
// 																	// compile-time constant
// }
namespace vs15 
{
	// define class copy and move ctor
	class X 
	{
	public:
		// default ctor
		X() : m_ptr2int(new int[5000]) {}
		~X() 
		{
			if (m_ptr2int != nullptr)
			{
				std::cout << "We are in the X::X() dtor" << "\n";
				delete[] m_ptr2int;
				m_ptr2int = nullptr;
			}
		}
		// copy ctor (allocate memory)
		X( const X& aOther) : m_ptr2int(new int[5000]) 
		{
			std::cout << "We are in the X::X(const X&) copy ctor" << "\n";
			
			// copy data across (use boost iterator range for stl algo compatibility)
			auto int_rng = boost::make_iterator_range( aOther.m_ptr2int, aOther.m_ptr2int+5000);
			std::copy( int_rng.begin(), int_rng.end(), m_ptr2int);
		}
		// move ctor (rvalue reference)
		X( X&& aOther) : m_ptr2int(aOther.m_ptr2int) // copy pointer to the data
		{
			std::cout << "We are in the X::X(const X&&) move ctor" << "\n";
			// leave other instance with pointer to nullptr 
			aOther.m_ptr2int = nullptr;
		}
	private:
		int* m_ptr2int;
		// must declared with const
		static constexpr unsigned m_arraySize = 5000;
	};

	// copy by value (take a const lvalue reference)
	void process_copy( std::vector<int> const& aVec)
	{
		// don't want to modify the original
		std::vector<int> w_vec(aVec);
		w_vec.push_back(42);
	}
	// what we do here? we still don't modify the original?
	// need to do some test
	// Important to note that the argument as no more const 
	// i think it doesn't make sense ... 
	void process_copy( std::vector<int>&& aVec)
	{
		aVec.push_back(42);
	}

	// ...
	void testCpp11Ctor()
	{
		using namespace std;

		// not sure what i'm doing here
		vector<int> w_vecofInt{};
		//check vector size

		// constant expression
		constexpr double PI2 = 3.141592653589793;
		static_assert(PI2 == 3.141592653589793, "");

		// compile-time assert 
		constexpr auto arraySize2 = 10;
		static_assert(arraySize2==10, "Array Size");
		//std::array<int, arraySize2> data2;  fine, arraySize2
																			 // is constexpr 

		// right-value (rvalue)
		int&& i = 42; // rvalue declaration

		// create an instance of our new class (with rvalue ctor)
		X w_x1;
	}
} // End of namespace