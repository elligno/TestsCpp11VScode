
//////////////////////////////////////////////////////////////////////////
//
//  FILE: Swe_Singleton.hpp

#ifndef singleton_HPP
#define singleton_HPP

// C++ includes
#include <iostream>
#include <cstddef>
// boost include
#include <boost/noncopyable.hpp>

namespace emcil
{
	// 
	// Global instance of the application
	// 
	template<class T>
	class Singleton : boost::noncopyable // private copy and  
	{                                    // assignment ctor
	  public:
		  // some methods 
		  static T* instance();
		  void release();
	  protected:

		  // We want to prevent of using them from client side
		  Singleton();

		  // Shouldn't the destructor be virtual?
		  virtual ~Singleton();
	  private:
		  // The sole instance of the class
		  static T* m_singleton;
	};

	// initialize static variable 
	template<class T> T* Singleton<T>::m_singleton = nullptr;

	template<class T>
	Singleton<T>::Singleton()
	{}

	template<class T>
	Singleton<T>::~Singleton()
	{
		// debugging purpose
		std::cout << "We are in the Singleton dtor\n"; 
	}

	template<class T>
	T* Singleton<T>::instance()
	{
		if( m_singleton == nullptr) 
		{
			m_singleton = new T;
		}

		return m_singleton;
	}

	template<class T>
	void Singleton<T>::release()
	{
		if( m_singleton == nullptr)
			return;

		delete m_singleton;
		m_singleton = nullptr;
	}
}  // End of namespace
#endif  // Include guard
