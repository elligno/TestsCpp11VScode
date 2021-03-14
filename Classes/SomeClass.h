
// similar to the ifndef... define ...endif
#pragma once

// C++ includes
#include <iostream>
#include <string>
// STL include
#include <list>
// class package
#include "IUpdateable.h"

#define constVar 3

// will be nice to use some of the new feature of the C++11
// Checking the SVN diff

// struct A
// {
// 	virtual void foo();
// 	void bar();
// };

// struct B : A
// {
// 	void foo() const override; // Error: B::foo does not override A::foo
// 	// (signature mismatch)
// 	void foo() override; // OK: B::foo overrides A::foo
// 	void bar() override; // Error: B::bar is not virtual
// };

namespace aa 
{
	//
	// a class 
	class TestAccess : public ITestAccess // inherit from the top abstract class
	{
	public:
		TestAccess();
		// no default ctor defined yet
		TestAccess( std::string alistOfInterface);
		TestAccess( const TestAccess& aOther);
        TestAccess& operator= ( const TestAccess& aOther);
		~TestAccess();
		// printing attribute
		void print();

		// return pointer to interface
		virtual void* getInterface( const unsigned aGuid) override;
    virtual void* getInterface( const std::string& aStr2Interface) = 0;
		void jeanTest( const float aFloat, unsigned aInt) ;
	protected:
		// want access right from derived class
		std::list<std::string> m_listofinterfaces;
		bool hasInterface() const; // check if this type support interface
	private:
		std::string m_strRep;
		int m_intVal;
	};
	
	//
	// Abstract class 
	//
	class BaseClass
	{
	public:
		// ctor summary
		BaseClass();   // default ctor
		// ctor with default value 
		BaseClass( int aInt,float aFloat, std::string aStr="JeanTest");
		~BaseClass(); // destructor

		// some class
		void myMethod() {std::cout << "This is myMetod() of the BaseClass\n";}

		// to be overided by subclass (virtual keyword dynamic binding)
		virtual void checKeyword() const { std::cout << "checKeyword Base class method\n";}
	private:
		std::string m_str;
		int m_intVal;
		float m_floatVal;
	};

	//
	// "inheriting class" (inherit from many interface, "COM" Component Object Model)
	// Access concept, component is accessible only by the interface supported.
	// This prototype class "inheritSomeClass" implement 2 interfaces.
	//
	class inheritSomeClass : public BaseClass,   // Base abstract class
		                     public TestAccess,  // Access class concept (COM approach mechanism) 
							 public IUpdateable, // something that is "updateable"
							 public IType        // Type of our framework
	{
	public:
		// ctor summary (be careful when passing by reference)
    // i don't see why we would want to pass by ref?
		inheritSomeClass( std::string& aStr);
		// ...
// 		inheritSomeClass( char* aName)
// 		: SomeClass(),
// 		  m_name()
// 		{
// 			std::cout << "Const char conversion ctor";
// 			m_charName=aName;
// 		}
		// default copy and assignment ctor will be fine

		// class methods
		const std::string& name() const { return m_name;}
		// this the derived version of myMethod
		void myMethod( float aVal=0) { std::cout << "This is myMethod() of inherited Some Class\n";}

		// C++11 keyword feature
		// In a member function declaration or definition, 
		// "override" ensures that the function is virtual and 
		// is overriding a virtual function from the base class.
		void checKeyword() const override { std::cout << "checKeyword Inherited Some Class method\n";}

		// jbTestA to query the interface supported by this component 
		void* getInterface( const std::string& aStr2Interface) override;
		// IUpdateable 
		void update() override     { std::cout << "update() method in inheritSomeClass\n";}
		// IType
		void type() const override { std::cout << "type() method in inheritSomeClass\n";}
	protected:
	private:
		// string name of the class
		std::string& m_name;
		char* m_charName;
	};
} // End of namespace