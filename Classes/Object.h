
#pragma once

// C++ includes
#include <iostream>
#include <string>

namespace aa 
{
   class Object
   {
   public:
	  Object()=default;
	  virtual std::string name() const { return std::string{"Object"};}
   protected: 
      //allow implicit conversion only from derived class
      Object(const Object& aOther)=default;
      Object(      Object&& aOtheer)=default;
   //slicing problem
   };	
} // End of namespace