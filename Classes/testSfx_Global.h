
// Doxygen documentation

    /**
     * \file testSfx_Global.h
     *
     * \author Jean Belanger (Elligno Inc.)
     * \date
     *
     * We are testing the concept of a global instance.
	 * It's very usefull to have a calss that carry all
	 * global functionalities of te applications.
     */

#ifndef sfxglobal_H
#define sfxglobal_H

// STL 
#include <map>
// boost 
#include <boost/ptr_container/ptr_map.hpp>
// app. 
#include "testSfx_Type.h"
#include "testSfx_Provider.h"
#include "Class.h"

namespace testSfx
{
	/**
	 * Hold global functionalities of the applications.
	 * Global is the following: mainly a global variable
	 * that is used throughout the code to support
	 * the global properties of the application. Initialized
	 * at startup. This concept will be reviewed in the future.
	 * Design Note: could we implement this global concept 
	 * as a singleton design pattern, i don't see why not.
	 */
	class Global
	{
	public: // i am not sure about this doc below
		/** @typedef mapofprov
		 * Map of providers (...)
		 */
		typedef std::map<std::string/*key*/, Provider* /*value*/> mapofprov;
		// to implement the factory methods design pattern
		typedef std::map<std::string/*key*/,aa::Class* /*value*/> mapofclass;
	public:
		Global(); /**< default ctor */
		~Global(); /**< destructor */
		/** 
		 * Add a framework type to the list.
		 * This is a simulation type one of our simulation 
		 * environment.
		 * @param aType to be added
		 */
		void addType( Type* aType);
		/**
		 * Add to the map container (Class instance)
		 * Usage:
		 *   
		 */
		void addClass( std::string aKey, aa::Class* aCls)
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

		aa::Class* getClass(const std::string aName) { return nullptr;}

		/**
		 * Return the type if it exist, if doesn't exist
		 * what do we do?? return a null pointer
		 * @param aType2Look to look for
		 * @result return the type or null if fail to find it
		 */
		Type* getType( const std::string& aType2Look);
		/** 
		 * Search for specific provider, and return it if found
		 * it returns the instance if it exist. 
		 */
		bool lookupProvider( Provider* aProv);
		/** 
		 * Add a provider ... to be completed
		 */
		void insertProvider( Provider* aProv);
		// add a function pointer (deprecated in C++11, shall use the function)
		void addTestFunc( const std::string& aStr/*nmaespace??*/, void (*)());
	protected:
	private:
		std::map<std::string, Type*> m_Dictionary; /**< System Type map */
		std::map<std::string/*key*/, Provider* /*value*/> m_Prov; /**< list of all provider */
		boost::ptr_map<const std::string,Type> m_pDictionary; /**< Boost implementation */
		// testing some map function management
		std::map<const std::string, void (*)()> m_func2test;
		mapofclass m_classInst;
	};
} // End of namespace

// global variable initialized outside
extern testSfx::Global* g_pGlobal;
#endif // End of namespace