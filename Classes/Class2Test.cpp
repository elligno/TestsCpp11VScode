#include "Class2Test.h"

// initialize static variable
int vs11::StaticVarTest::m_sVar=0;
//Bus::Driver* m_sMember=nullptr; 
int vs11::SomeClass::data=0;

namespace vs11 
{
 //   Bus::Driver* Bus::createDriver()
 //   {
        //return new int;
        //   if (m_sMember == nullptr)
        //       m_sMember = new Driver;

        // m_sMember = new Driver;
        //return m_sMember;
  //      return new Bus::Driver;
  //  }

   SomeClass::SomeClass( const SomeClass& aOther)
   {
     std::cout << "we are in SomeClass copy ctor\n";
   }

   SomeClass &SomeClass::operator=(const SomeClass &aOther)
   {
     std::cout << "we are in the SomeClass assignment ctor\n";
     return *this;
   }
} // End of namespace