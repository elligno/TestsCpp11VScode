
 #pragma once

// C++ includes
#include <utility>
#include <iostream>
// C++20 include
#include <ranges>

namespace Btl
{
	// print stl-like container (interface)
	template<typename Cont> // container
	void printCont( const Cont& aCont2print)
	{
		// define a type
		using const_iterator = typename Cont::const_iterator;

		// initialize the iterator
		const_iterator beg = aCont2print.begin();
		const_iterator end = aCont2print.end();
		// printing elements
		while(beg!=end)
		{
			std::cout << *beg++ << "\n";
		}
	}

	// print a pair 
	template<typename T1, typename T2>
	std::ostream& operator<< ( std::ostream& aStrm, const std::pair<T1,T2>& aPair)
	{
		return aStrm << "[" << aPair.first << "," << aPair.second << "]";
	}

	// ______________________________________________________________
	//
	template<typename Rng>
	void printRange( const Rng& aRange2Print)
	{
		std::cout << "We are printing the range\n";
		
		// range concept C++20 (sanity check)
		static_assert(std::ranges::range<Rng>);

		// C++20 range algorithm
		std::ranges::copy(aRange2Print, // range to print
						  std::ostream_iterator<std::ranges::range_value_t<Rng>>(std::cout, "\n"));
	}

	// _______________________________________________________
	//
	//      print container (STL-like container)
	//
	template<typename CONT> // container
	void print_container( const CONT& aCont2Print)
	{
		// typename because CONT is a argument template 
		// we have to give an hint to the compiler
		// container element type
		// typedef typename CONT::value_type ctype;
		// // define an iterator and a const iterator
		// typedef typename CONT::iterator iter_range;
		// typedef typename CONT::const_iterator citer_range;

		// //  initialize range iterators
		// citer_range w_beg = aCont2Print.begin();
		// citer_range w_end = aCont2Print.end();
		// std::copy(w_beg,w_end, 
		// 	std::ostream_iterator<ctype>(std::cout," "));
		
		// C++20 way of doing thing
		static_assert(std::ranges::range<CONT>); //sanity check
		// range concept C++20  
		std::ranges::copy(aCont2Print,
			std::ostream_iterator<std::ranges::range_value_t<aCont2Print>>(std::cout," "));
		std::cout << "\n";
	}
} // End of namespace