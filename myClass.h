#pragma once

// C++ include
#include <iostream>

namespace vs11 
{
    class myClass //: public Object // base object
                //    public IInterface2Impl // interface 
    {
        public:
        explicit myClass(unsigned aUint);

        // services
        void printSelf() {}
    };

    class TestClass 
    {
        public:
          TestClass();
          // Usage: TestClass myClass {{1,2.3} {2,4.12}};
          // is it correct?
          TestClass( int aIntval, float aFloatval);
          TestClass( const TestClass& aOther);
          TestClass& operator= ( const TestClass& aOther);
          // setter/getter
          size_t length() const     {return m_length;}
          int getIntVal() const     {return m_intVal;}
          float getFloatVal() const {return m_floatVal;}

          void resize();
        private:
        // set value as default
        // question: these settings will be apply to all ctor?
        // Let say i declare 
        // TestClass w_jeanTT;  all variable will be set to these values below?
        size_t m_length=5;
        int m_intVal=0;
        float m_floatVal=0.f;
        short* m_arrayofShort=nullptr;
    };
  }  // End of namespace