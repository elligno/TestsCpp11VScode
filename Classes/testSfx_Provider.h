
// Author: Jean Belanger (Elligno Inc.)
// Date of creation: Unknown
// Revision history:

#ifndef testsfxprovider_H
#define testsfxprovider_H

// C++ includes
#include <iostream>
#include <string>

namespace testSfx
{
	/** 
	 * Base class of the provider concept. It is at the heart
	 * of our programming environment (concept of a global instance)
	 * The implementation support only partial functionality of the 
	 * provider concept, it will be completed later in our development. 
	 * Provider is a very important concept of our application, as
	 * the name say it provides a global functionalities to our app.
	 */
	class Provider 
	{
	public:
		/**
		 * Default ctor.
		 */
		Provider(): m_str("Provider Base Class") {/*nothing to do*/}
		/** 
		 * Destructor
		 */
		virtual ~Provider() { std::cout << "We are in the provider dtor\n";}
	protected:
		static Provider* m_sProv;    /**< provider instance*/
	private:
		std::string m_str; /**< Provide name*/
	};
} // End of namespace
#endif // Include guard