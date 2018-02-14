#include "myClass.h"

namespace vs11 
{
    //
    // TestClass implementatin
    //
    
    TestClass::TestClass(int aIntval, float aFloatval)
    : m_intVal(aIntval),
      m_floatVal(aFloatval)
      {
          // tace
          if(m_arrayofShort==nullptr)
          {
              m_arrayofShort = new short[m_length];
          }
      }

    TestClass::TestClass(const TestClass& aOther)
    : m_length(aOther.m_length),
      m_intVal(aOther.m_intVal),
      m_floatVal(aOther.m_floatVal)
    {
        // tarce for debugging purpose
        std::cout << "TestClass copy ctor\n";

        if (m_arrayofShort)
            delete[] m_arrayofShort;

        m_arrayofShort = new short[aOther.length()];
    }

    TestClass& TestClass::operator= ( const TestClass& aOther)
    {
        // trace for debugging
        std::cout << "TestClass operator=\n";

        // check for self-assignment
        if(this != &aOther)
        {
            // not self-assignment
            m_length = aOther.m_length;
            m_intVal = aOther.m_intVal;
            m_floatVal = aOther.m_floatVal;
        }
        return *this;
    }
} // End of namespace