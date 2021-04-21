#pragma once

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
	{
	public:
	// default ctor
	AlgorithmClass();
    ~AlgorithmClass();
	AlgorithmClass( const AlgorithmClass& aOther) = delete;
	AlgorithmClass& operator= ( const AlgorithmClass& aOther) = delete;
		
    // Class interface (kind of factory, actually 
	// it's a factory method Design Pattern)
	void* newInstance() override;
	};
} // End of namespace