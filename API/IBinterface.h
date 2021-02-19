
//  Author: Jean Belanger (Elligno inc.)
//  Date of creation: unknown
//  Revision history:

#ifndef testsfxibinterface_H
#define testsfxibinterface_H

// app. include (i am not sure what i want to do)
#include "testSfx_Provider.h"

// I do not think that it does anything in the documentation

/** @def jeandef
 * This define is just a test for documentation (not used).
 */
#define jeandef 1

namespace testSfx 
{
	/**
	 * We want to implement the provider mechanism.
	 * interface, a provider is a kind of singleton.
	 * but can support many interface.
	 */
	class IBinterface
	{
	public:
		/** @typedef float32
 		 * for clarity and cross-platform support.
		 */
		typedef float float32;
	public:
		/** @struct checkDoc
		 *  @brief This is a simple structure to hold some data.
		 */
		struct checkDoc 
		{
			float m_floatVal;   /**< Single value*/
			double m_doubleVal; /**< Double value*/
		};
	public:
		/**
		 * A constructor.
		 * Default ctor.
	 	 */
		IBinterface();

		/** 
		 * A destructor.
		 * destructor is virtual.
		 */
		virtual ~IBinterface(void);
		
		/** 
		 * Provider implementation of the interface.
		 * Provider concept is a global instance of the application.
		 */
		static IBinterface* getProvider();
		/**
		* lookupProvider
		*
		* @return bool
		* @param  aProv
		*/
		bool lookupProvider( Provider* aProv);
		/**
		* doSomething
		*
		* @return void
		* @param  
		*/
		virtual void doSomething()=0;
	protected:
 		static IBinterface* m_sProvInstance; /**< sole instance of the provider. */
	private:
	};
} // End of namespace 
#endif // Include guard