#include <iostream>
#include <vector>
#include <initializer_list>

namespace vs15 
{
	template <class T>
	struct Structest 
	{
		std::vector<T> vec;

		Structest( std::initializer_list<T> alist) : vec(alist) 
		{
			std::cout << "constructed with a " << alist.size() << "-element list\n";
		}
		
		void append( std::initializer_list<T> alist) 
		{
			// vector insert at the end (inserts elements from range [first, last) before pos.)
			vec.insert( vec.end(), alist.begin(), alist.end());
		}
		
		std::pair<const T*, std::size_t> c_arr() const 
		{
			// return a pair with the new feature of C++14 
			return {&vec[0], vec.size() };  // copy list-initialization in return statement
																	    // this is NOT a use of std::initializer_list
		}
	};

	// new feature of the C++14
	void testListInitializer()
	{
		Structest<int> w_s = { 1, 2, 3, 4, 5 }; // copy list-initialization
		w_s.append({ 6, 7, 8 });      // list-initialization in function call

		std::cout << "The vector size is now " << w_s.c_arr().second << " ints:\n";

		for (auto n : w_s.vec)
			std::cout << n << ' ';
		std::cout << '\n';
	}
} // End of nmaespace