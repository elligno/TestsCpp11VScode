#pragma once

#include <boost/noncopyable.hpp>

// __________________________________________________________
//
// This implementation is based on Scott Meyers', using a 
// function static and returning a reference. It also uses 
// James Coplien's curious recurring template pattern.
//
// To make a class a singleton, derive it from this template, 
// passing the derived class as a template parameter:
//
// class MySingleton : public Sfx_Singleton <MySingleton>
//
namespace aa 
{
	template<typename T> class TestSingleton 
		: public boost::noncopyable
	{
	public:	  
		static T& getSingleton();
	protected:
		// Default constructor
		TestSingleton();

		// Force destructor to be virtual (It is a pure virtual function, 
		// it means it is left to derived class to implement the destructor).
		// It is not the intent of this class to delete, let it to the subclass. 
		virtual ~TestSingleton() = 0;
	private:
		// Copy constructor (make it private ...)
//		TestSingleton( const TestSingleton & aOther); 
		// Assignment operator
//		TestSingleton & operator = ( const TestSingleton & aOther);
	};

	//
	// Inline definitions
	//

	// ______________________________________________________________________
	//
	template<typename T> inline TestSingleton<T>::TestSingleton()
	{
		std::cout << "We are in the TEstSingleton ctor\n"; 
	}

	// _______________________________________________________________________
	//
	template<typename T> inline TestSingleton<T>::~TestSingleton()
	{
		std::cout << "We are in the TestSingleton dtor\n";
	}

	// _______________________________________________________________________
	//
	template< typename T> inline 
		T & TestSingleton<T>::getSingleton()
	{
		static T wSingleton; // persistence through the application 
		                     // instead of dynamically allocate it 
		return wSingleton;
	}
}  // End of namespace
