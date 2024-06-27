
  // Author: Jean Belanger (Elligno Inc.)
  // Date of creation: January 20, 2011
  // Revision history:

#ifndef btlprintutils_HPP
#define btlprintutils_HPP

// C++ includes
#include <utility>
#include <iostream>

namespace Btl
{
	// print stl-like container (interface)
	template<typename Cont> // container
	void printCont( const Cont& aCont2print)
	{
		// define a type
		typedef typename Cont::const_iterator const_iterator;

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
	template<typename Range>
	void printRange( const Range& aRange)
	{
		std::cout << "We are printing the range\n";
		typedef boost::range_iterator<Range>::type iter_type;
		typedef std::iterator_traits<iter_type>::value_type value_type;
		std::copy( boost::begin(aRange), boost::end(aRange),
			std::ostream_iterator<value_type>(std::cout,"\n"));
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
		typedef typename CONT::value_type ctype;
		// define an iterator and a const iterator
		typedef typename CONT::iterator iter_range;
		typedef typename CONT::const_iterator citer_range;
		//  initialize range iterators
		citer_range w_beg = aCont2Print.begin();
		citer_range w_end = aCont2Print.end();
		std::copy(w_beg,w_end, 
			std::ostream_iterator<ctype>(std::cout," "));
		std::cout << "\n";
	}
} // End of namespace
#endif // Include guard
