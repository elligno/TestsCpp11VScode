
#ifndef ffalgorithm_H
#define ffalgorithm_H

#include "IUpdateable.h"

namespace aa 
{
	// Some numerical flux algorithm at cell face 
	// in a finite volume discretization.
	class FFAlgorithm : public IConservative 
	{
	public:
		void calculFF() override
		{
			std::cout << "We are in the calculFF() function\n";
		}
	private:
	};
} // End of namespace
#endif // !ffalgorithm_H
