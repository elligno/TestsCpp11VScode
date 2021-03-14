
// Author: Jean Belanger (Elligno Inc.)
// Date of creation: 2009
// Revision history:
//  Jean Belanger -- 22-jan-2010
//  From the original version in VS2005, under project "DesignValidate"

#include <vector>
// Package includes
#include "AlgorithmClass.h"
#include "testSfx_Global.h"
//#include "Global.h"
// HydApp package include
//#include "HydApp/Dsn_DamBreakSim.h"
#include "FFAlgorithm.h"
#include "TestLogger.h"

static int x=2;
static std::string s_str = "Check static variable initialization";

int printStatic()
{
	std::cout << "This is the static string: " << s_str << "\n";

	return 0;
}

static std::vector<std::string> w_sVecstr;
int fillStaticVec() 
{
	std::cout << "Filling static vector in AlgorithmClass\n";

	w_sVecstr.push_back(std::string("toutou"));
	w_sVecstr.push_back(std::string("negrito"));
	
	return 0;
}
namespace aa
{
    int w_retVal=fillStaticVec();

	// create an instance
	AlgorithmClass m_AlgoClassname;   

	// default ctor
	AlgorithmClass::AlgorithmClass()  
	{
		// this is a trace for debugging purpose
		std::cout << "AlgorithmClass::AlgorithmClass() ctor\n";
		std::cout << "x value is: " << x << "\n";

		// check size of the vector
		if( w_sVecstr.size()!=0)
		{
			std::cout << "Static vector is not empty\n"; 
		}
		// retrieve a reference from 
		TestLogger& w_checkPtrInit = TestLogger::getSingleton();
		// add system or simulation type
		TestLogger::getSingleton().addClass( std::string("test123"), &m_AlgoClassname);
		
		// add the type to the system (can be retrieved by it's name)
		// loaded at simulation startup (from config file or something 
		// like this).
		// need to merge both global class before using this global variable
		// temporary fix (debugging purpose)
//		g_pGlobal->addClass( std::string("FFAlgorithm"), &m_AlgoClassname);
	}
	AlgorithmClass::~AlgorithmClass()
	{
		// do nothing for now
	}
	// shall return an Object class instead of void pointer
	void* AlgorithmClass::newInstance()
	{
		// need a base pointer IPhysicalAlgorithm
		// actually it should return the type that 
		// inherit from a base class, this way you 
		// can cast to this base type. 
//		DamBreakSim* w_sim = new DamBreakSim();
		//return w_sim;
		return new FFAlgorithm; // debugging purpose
	}
} // End of namespace