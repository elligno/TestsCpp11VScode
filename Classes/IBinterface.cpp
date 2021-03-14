
#include "IBinterface.h"
#include "testSfx_Global.h"

namespace testSfx
{
	// initialize the static variable
	IBinterface* IBinterface::m_sProvInstance=nullptr;

	IBinterface::IBinterface(void)
	{
	}
	IBinterface::~IBinterface(void)
	{
	}
	IBinterface* IBinterface::getProvider()
	{
// 		g_pGlobal->lookupProvider()
// 		if (m_sProvInstance==NULL)
// 		{
// 		}
		return m_sProvInstance;
	}
} // End of namespace
