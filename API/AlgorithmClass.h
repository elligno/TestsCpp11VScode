

#ifndef algorithmclass_H
#define algorithmclass_H

// boost includes
#include <boost/noncopyable.hpp>
// Package include
#include "Class.h"

namespace aa
{
	// Usage:
	// -------
	//   Factory Methods Design Pattern
	//    AlgorithmClass* w_algoClass = Class::forname("EMcNeilAlgo");
	//    IAlgorithmClass* w_Ialgo = (IAlgorithmClass*)w_algoClass->newInstance();
	//    
	class AlgorithmClass : public Class
		                  // boost::noncopyable
	{
	public:
		// default ctor
		AlgorithmClass();
    ~AlgorithmClass();
		// Class interface (kind of factory, actually 
		// it's a factory method Design Pattern)
		void* newInstance() override;
	protected:
		// boost noncopyable
// 		AlgorithmClass( const AlgorithmClass& aOther);
// 		AlgorithmClass& operator= ( const AlgorithmClass& aOther);
	private:
		// instance counter
	};
} // End of namespace
#endif // Include guard