
#pragma once

// C++ include
#include <iostream>
// project include
#include "../Classes/NocpyAssgnClass.h"

namespace vs15 
{
	void testCopyAssgnCtor()
	{
		// create with default ctor
		const NocpyAssgnClass w_testDef;

		// let's print and see what we got here
		const float w_checkFloat = w_testDef.getFloat32();
		std::cout << "What we got here\n";
		std::cout << "Float value is: " << w_checkFloat << "\n";
	}

}// End of namespace