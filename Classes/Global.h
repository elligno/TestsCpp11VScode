
#pragma once

// C++ include
#include <string>
// STL include
#include <map>
// Package includes
#include "Object.h"
#include "Class.h"

namespace aa
{
	// act as a global variable to add functionality to the system
	class Global
	{
	public:
		Global();
		~Global();
		void addType( const std::string& aId, Class* aClass);
		void* getType( const std::string& aId);
	protected:
	private:
       // std::vector<std::pair<const char*,Class*> > w_vecpair;
		// shall use boost ptr_map for container of pointer
	    std::map<std::string, Class*> m_MapClass;
	};
} // End of namespace

// global variable
extern aa::Global* g_pGlobale;