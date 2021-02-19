
// C++ includes
#include <cstdio>
#include <cstdlib>
#include <stdarg.h>
#include <utility>
//#include <vector>
// conversion macros
#include <AtlBase.h> 
#include <AtlConv.h>

// Package include
#include "Global.h"

namespace aa
{
	// Initialize static variable
	static int WarningCount = 0;

	Global::Global(/*do nothing*/) {}
	Global::~Global()
	{
		// empty the container and delete it
 		if( !m_MapClass.empty())
 		{
// 			std::map<const char*, Class*>::iterator w_iter = m_MapClass.begin();
// 			while( w_iter!=m_MapClass.end())
// 			{
// 				Class* w_class2Del = (*w_iter).second;
// 				delete w_class2Del;
// 			}
 		}
	}
	// register type to system (addType( "myName", Class* aClass))
	void Global::addType( const std::string& aId, Class* aClass)
	{
		const char* w_StrID="DamBreakSetup"; // debugging purpose
		m_MapClass.insert( std::make_pair( aId.c_str(), aClass));
	}
	// retrieve type from dictionary
	void* Global::getType( const std::string &aId)
	{
		void* w_ptr2Null=nullptr;
		// something wrong it doesn't compile
//  		std::map<const char*, Class*>::iterator w_objInstance=
//  			m_MapClass.find(aId.c_str());
//  		if( w_objInstance!=m_MapClass.end())
//  		{
// 			return (*w_objInstance).second;
//  		}
//  		else 
//  			return w_ptr2Null;
          return nullptr; // debugging purpose
	}
} // End of namespace