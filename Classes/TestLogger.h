
//  Author: Jean Belanger (Elligno Inc.)
//  Date of creation: December 10, 2013
//  Revision history:

#pragma once

// stl include
#include <map>
// package include
#include "TestSingleton.hpp"
#include "Class.h"

namespace aa 
{
	// Actually its not a logger, type manager that is used 
	// to store instance of some type of the framework. By
	// using a global variable declare as extern we face some 
	// problem at initialization start up,   
	class TestLogger :
		public TestSingleton<TestLogger>
	{
		// to implement the factory methods design pattern
		using mapofclass = std::map<std::string/*key*/,aa::Class* /*value*/>;
	public:
		// don't want to declare public, because only one instance
		// for the whole application no more. Block access to the 
		// client by forcing him to call getSingleton which manage
		// the sole instance.
		
// 		TestLogger(void);
// 		~TestLogger(void);

		// for now do nothing
		void addClass( const std::string& aKey, Class* aCls) 
		{
			mapofclass::iterator w_found=m_classInst.find(aKey);

			// before we add it just check if it already in 
			if( w_found!=m_classInst.end())
			{
				std::cout << "This value already inserted in the map\n";
				return;
			}

			// do some insert to the map container
			m_classInst.insert( std::make_pair(aKey,aCls));
		}

		aa::Class* getClass( const std::string aKey) 
		{ 
			mapofclass::iterator w_found = m_classInst.find(aKey);

			// before we add it just check if it already in 
			if( w_found!=m_classInst.end())
			{
				std::cout << "We found in the map\n";
				return w_found->second; // returns the object 
			}

			// since we didn't find anything return a null pointer 
			return nullptr;
		}

		// Method of the Logger class
		// Make this class a friend of the base class 
		friend class TestSingleton<TestLogger>;
	protected:
		TestLogger();
		~TestLogger();
 
	private:
		mapofclass m_classInst;
	};
} // End of namespace
