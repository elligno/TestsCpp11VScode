
#pragma once

// C++ includes
#include <iostream>
#include <string>

namespace testSfx 
{
	/**
	 * Abstract class for testing the framework.
	 * Implement/inherit from this class if you
	 * want your type be part of the framework (managed).
	 */
	class Type 
	{
	public:
		// default ctor
		Type(std::string aTypename="Type") 
    : m_typeName(aTypename) 
    {
      std::cout << "Type default ctor\n";
    }
		virtual ~Type() { std::cout << "Type destructor\n";}
		// These methods need to be overrided everytime 
		// Provide a default implementation (deprescated since C++11)
		virtual bool isAbstract()   const { return false;}
		virtual bool hasInterface() const { return false;}
		virtual bool isClass()      const { return false;} 
		virtual bool isStruct()     const { return false;}
    
    // Type method (provide a short description)
		virtual std::string descr();
		virtual const std::string& name() const { return m_typeName;}
	protected:
		std::string m_typeName;
	private:
		/** 
		 * Copy ctor 
		 * @param aOther another Type
		 */
		Type( const Type& aOther);
		/** 
		 * Assignment ctor
		 * @ aOther another type
		 */
		Type& operator= ( const Type& aOther);
		/**
		 * This is an instance counter, similar to reference count
		 * each time a type is created, the instance counter is updated. 
		 */
	};
} // End of namespace