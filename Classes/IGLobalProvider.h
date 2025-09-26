#pragma once

#include <string>

namespace tst 
{
  // Check in the book of Design Pattern (GOF) the 
  // Singleton Design Pattern chapter where an alternative
  // design is proposed which is close to the concept
  // of CAE provider ()
  // 
  class IGlobalPRovider 
  {
  public:
    virtual void printSelf()=0;
    virtual std::string name()=0;
  protected:

    // global instance of the provider
    static IGlobalPRovider* m_sprovider;
  };
} // End of namespace