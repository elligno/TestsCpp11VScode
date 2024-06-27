
//  Author: Jean Belanger (Elligno Inc.)
//  Date of creation: November 29, 2013 

// C++ include
#include <iostream>
// STL include
#include <algorithm>
// library include
#include "SomeClass.h"

namespace aa 
{
	// ________________________________________________________________
	//
	// set default value ctor

	BaseClass::BaseClass(void)
	: m_str("BaseClass"),
	  m_intVal(0),
	  m_floatVal(0.)
	{
		std::cout << "BaseClass default ctor\n";
	}

	// ________________________________________________________________
	//
	// ctor
	BaseClass::BaseClass( int aInt/* =2 */, float aFloat, std::string aStr/* ="JeanTest" */)
    : m_str(aStr),
	  m_intVal(aInt),
	  m_floatVal(aFloat)
	{
		std::cout << "";
	}

	// ________________________________________________________________
	//
	// destructor
	BaseClass::~BaseClass(void)
	{
    std::cout << "BaseClass dtor\n";
	}

	// ...
	inheritSomeClass::inheritSomeClass( std::string& aStr)
	: BaseClass(),
	  TestAccess("IDisplayable IUpdateable IType"),
	  m_name(aStr)  
	{ 
		std::cout << "CSring conversion ctor\n";
	}
	
	// inherited from Access mechanism interface
	void* inheritSomeClass::getInterface( const std::string& aStr2Interface)
	{
		std::cout << "getInterface() of inherit\n";

		if (hasInterface()) // support interface
		{
// 			if ( ::strcmp("IDisplayable",aStr2Interface.data())==0)
// 			{
// 				return static_cast<aa::IDisplayable*>(this);
// 			}
			if ( ::strcmp("IUpdateable",aStr2Interface.data())==0)
			{
				return static_cast<aa::IUpdateable*>(this);
			}
// 			else if( ::strcmp("IConservative",aStr2Interface.data())==0)
// 			{
// 				return (aa::IConservative*)this;
// 			}
			else if( ::strcmp("IType",aStr2Interface.data())==0)
			{
				return static_cast<aa::IType*>(this);
			}	
			else
			{
				return nullptr;
			}
		}
		else
		{
			return nullptr;
		}
	}

	//
	// jbTestA
	//

	TestAccess::TestAccess()
		: m_strRep("jbTestA"), 
		m_intVal(0) 
	{ 
		std::cout << "Default ctor jbTestA\n"; ++m_intVal;
	}

	// ...
	TestAccess::TestAccess( std::string alistOfInterface) 
	: m_strRep(alistOfInterface),
	  m_intVal(1)
	{ 
		std::cout << "jbTestA string ctor\n";
		// split the string in parts (find method)
		while (m_strRep.find(" ")!=std::string::npos)  // go through the string
		{
			// retrieve substring
			std::string::size_type w_first=m_strRep.find_first_of(" ");
			if (w_first!=std::string::npos) // sanity check for empty string
			{
				// we found one, then extract the interface name (start to last index)
				std::string w_intefaceName=m_strRep.substr( 0, w_first);
				if (!w_intefaceName.empty())
				{
					// push each string (list of string)
					m_listofinterfaces.push_back(w_intefaceName);
					// remove substring from the whole string
					m_strRep.erase(0,w_first+1); // now we have a modified string
				}
			}
		}
		if (!m_strRep.empty() && (m_strRep.length()!=0))
		{
			// there is one left (interface name)
			m_listofinterfaces.push_back(m_strRep);
		}
	}
	// copy ctor
	TestAccess::TestAccess( const TestAccess& aOther )
	{
    m_strRep=aOther.m_strRep;
		m_intVal=aOther.m_intVal;
		// what we do the list attributes, check if it is empty
		if ( !m_listofinterfaces.empty()) // if not 
		{
			// empty the list
			m_listofinterfaces.clear(); // now ready to copy new elements in the list
			std::copy( aOther.m_listofinterfaces.begin(),aOther.m_listofinterfaces.end(),
			m_listofinterfaces.begin());
		 }
		else
		{
			std::copy( aOther.m_listofinterfaces.begin(),aOther.m_listofinterfaces.end(),
				m_listofinterfaces.begin());
		}
	}
	// 
	TestAccess& TestAccess::operator= (const TestAccess& aOther)
	{
		// check for self assignment
		if (this==&aOther)
		{
			return *this;
		}

		// now empty the list
		return *this;
	}

	TestAccess::~TestAccess()
	{
		// empty the container (list)
    std::cout << "TestAcces dtor\n";
	}
  
  // search for the supported interface
	bool TestAccess::hasInterface() const
	{
		// check for supported interface
		using dist = std::iterator_traits<std::list<std::string>::iterator>::difference_type;
		dist w_distInterface = std::distance( m_listofinterfaces.cbegin(), m_listofinterfaces.cend());
		if (w_distInterface == 0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	// just for testing VA tool 
	void TestAccess::jeanTest( const float aFloat, unsigned aInt)
    {
		const float w_val=aFloat;
		std::cout << "Floating value is: " << w_val << "\n";
	}

	void TestAccess::print()
	{
		std::cout << "Print method of jbTestA class\n";
		std::cout << "String attribute is: " << m_strRep.c_str() << "\n";
		std::cout << "Integer attribute is: " << m_intVal << "\n";
	}
	
	void* TestAccess::getInterface( const unsigned aGuid )
	{
		if( aGuid == IID_IConservative)
			return getInterface("IConservative");
		else if( aGuid == IID_IType)
			return getInterface("IType");
		else if( aGuid == IID_IDisplayable )
			return getInterface("IDisplayable");
		else if( aGuid == IID_IUpdateable)
			return getInterface("IUpdateable");
		else
			return NULL;
	}

} // End of namespace

