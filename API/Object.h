
//  Author: Jean Belanger (Elligno Inc.)
//  Date of creation: May 19, 2014
//  Revision history:

#ifndef object_H
#define object_H

// C++ includes
#include <iostream>
#include <string>
// boost include
#include <boost/noncopyable.hpp>

namespace aa 
{
   class Object : boost::noncopyable // shall inherit from boost noncopyable
   {
   public:
	   Object() {/*need a default ctor*/}
	   Object( const std::string& aName): m_name(aName) {}
	   const std::string& name() const { return m_name;}
	   
	   // Object interface
	   //
	   //	bool equals( const Object& aOther) { return false;}
   protected: 
     // i don't understand why it should be accessible from inherited class
	   // not accessible from outside
// 	   Object( const Object& aOther)
// 	   {
// 		   std::cout << "Object copy ctor\n";
// 	   }
// 	   Object& operator= (const Object& aOther)
// 	   {
// 		   std::cout << "Object assignment ctor\n";
// 		   return *this;
// 	   }
	   // protected attribute
	   std::string m_name;
   private:
   };	
} // End of namespace
#endif