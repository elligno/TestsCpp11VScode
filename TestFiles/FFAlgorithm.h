
#pragma once

// C++ include
#include <iostream>
// App include
#include "IUpdateable.h"

namespace aa 
{
	/**
	 * @brief Some numerical flux algorithm at cell face in a finite volume discretization. 
	 */
	class FFAlgorithm : public IConservative 
	{
	public:
	/**
	 * @brief Compute numerical flux at cell face
	 * 
	 */
		void calculFF() override
		{
			std::cout << "We are in the calculFF() function\n";
		}
	};
} // End of namespace