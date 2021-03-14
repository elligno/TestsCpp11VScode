
// Package includes
#include "Class.h"
#include "testSfx_Global.h"
#include "TestLogger.h"

static int y;
int anotherPrint()
{
	std::cout << "Value of the static variable y is: " << y << "\n"; 

	return 0;
}
namespace aa
{
    // retrieve ... to be completed
	Class* Class::forName( const std::string &aName)
	{
		// need to merge both classes (Global) before using this global variable
	//	return (Class*)g_pGlobal->getType(aName);
	//	return g_pGlobal->getClass(aName);
		TestLogger& w_checkPtrInit = TestLogger::getSingleton();
		Class* w_cls = TestLogger::getSingleton().getClass( std::string("test123"));
		if (w_cls!=nullptr)
		{
			return w_cls;
		}
		else
			return nullptr;
	}
	// to be overriden by subclass ()
	void* Class::newInstance()
	{
		// it should be declared as pure abstract class
		return nullptr;
	}
} // End of namespace