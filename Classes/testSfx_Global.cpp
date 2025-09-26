
//  Author: Jean Belanger (Elligno Inc.)
//  Date of creation: April 14, 2014 
//  Revision history:

// C++ include
#include <utility>
// test include
#include "testSfx_Global.h"

namespace testSfx
{
	// ________________________________________________
	//
	Global::Global()
	{
		// nothing to do
	}
	// ________________________________________________
	//
	Global::~Global()
	{
		typedef std::map<std::string, Type*> dictionary;
		if( !m_Dictionary.empty())
		{
			dictionary::iterator beg=m_Dictionary.begin();
			dictionary::const_iterator end=m_Dictionary.end();
			while( beg!=end)
			{
				Type* w_pType=(*beg).second;
			}
		}
	}
	// ________________________________________________
	//
	void Global::insertProvider( Provider* aProv)
	{
		// provide an implementation (add the provider to the dictionary)
		// when we add a type to the map, pair<...,...>
		// map element is a pair (key,value) pair
		
		// first retrieve name of the provider
		// it is the key of the provider, we will ...
		// then insert (instance or pointer) to the map
// 		std::string 
// 		m_Prov.insert(std::pair<aProv>);
	}
	// ________________________________________________
	//
	bool Global::lookupProvider( Provider* aProv)
	{
		// search for the provider (need the key)

		// debugging purpose
		return false;
	}
	// ________________________________________________
	//
	void Global::addType( Type* aType)
	{
		// create an auto pointer to ensure that the object 
		// is deleted whatever happens.
		// NOTE: auto_ptr not anymore supported in the C++11
		// need to use the unique pointer

		// just don't get it since we are using a ptr container
		// takes the ownership of the pointer and delete it
		std::unique_ptr<Type> w_temp{aType};

		if( aType) // check if type is null
		{ 
			// then add it to the container (boost container of pointer)
			std::cout << "We are just about to add the following type: " << aType->name() << "\n";
			m_pDictionary.insert( aType->name(),/*aType*/ std::move(w_temp));
			std::cout << "Type added successfully\n";
		}
	}
	// ________________________________________________
	//
	Type* Global::getType( const std::string& aType2Look)
	{
		// check if type exist
		return nullptr; // not found
	}
} // End of namespace