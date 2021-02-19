
#ifndef class_H
#define class_H

// C++ include
#include <string>

// Framework object
#include "Object.h"

namespace aa
{
  // just testing some inheritance stuff
	class Class : public Object
	{
	public:
		Class() : Object( std::string("Class")) {} // default ctor
		virtual ~Class() {/*do nothing*/}
		static Class* forName( const std::string& aName);
		virtual void* newInstance();  //=0; ?? pure abstract, isn't?
	protected:
		Class( const Class& aOther)
		{
			std::cout << "Class copy ctor\n";
		}
		Class& operator= (const Class& aOther)
		{
			std::cout << "Class assignment ctor\n";
			return *this;
		}
	private:
	};
} // End of namespace
#endif // Include guard