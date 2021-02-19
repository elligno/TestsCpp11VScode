#include "ClassVS15.h"

using namespace vs15;



vs15::Classvs15::Classvs15(int y /*= 10*/) : m_y(y)
{

	std::cout << "default ctor\n";
	m_vec.reserve(m_y); // allocate memory to store data
}
