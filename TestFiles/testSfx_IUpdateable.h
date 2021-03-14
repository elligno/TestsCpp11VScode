#pragma once

// C++ include
#include <iostream>

namespace testSfx
{
	/**
	 * Use this interface for a callback mechanism.
	 * implementation through interface concept.
	 */
	class IUpdateable 
	{
	public:
		/** 
		 * This method need to be implemented by the derived class.
		 * A pure virtual member.
		 */
		virtual void update()=0;
	protected:
		/**
		 * Dtor is declared virtual and protected for the following reason.
		 * which i do not remember (to be completed later).
		 */
		virtual ~IUpdateable() { std::cout << "We are in IUdateable dtor\n";}
	};
} // End of namespace