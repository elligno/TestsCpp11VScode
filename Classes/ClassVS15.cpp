#include "ClassVS15.h"

using namespace vs15;

vs15::Classvs15::Classvs15(int y /*= 10*/) 
: m_name{"Classvs15"},
  m_y(y),
  m_vec(m_y)
{
	std::cout << "default ctor\n";
	if (m_vec.empty())
	{
		std::cout << "Parameters list initialization make me crazy\n";
	}
	
	m_vec.resize(5); // allocate memory to store data
	auto i=0;
	for( auto val : m_vec)
	{
		/* code */
		m_vec[i++]=0;
	}
}

#if 1 // needed for temporaries even if not used it has tyo be declared/defined
    // talking about copy elison features of C++17. 
vs15::Classvs15::Classvs15( Classvs15&& aOther)
{
	std::cout << "Classvs15 move ctor\n";
	m_y = aOther.m_y;
	m_vec = std::move(aOther.m_vec); // swap resource avoid coping value
}
#endif

#if 1 // copy not allowed
vs15::Classvs15::Classvs15( const Classvs15& aOther)
{
	std::cout << "Classvs15 copy ctor\n";
	m_y = aOther.m_y;
	m_vec.reserve(aOther.m_vec.size());
	std::copy( aOther.m_vec.cbegin(), aOther.m_vec.cend(), m_vec.begin()); 
}
#endif