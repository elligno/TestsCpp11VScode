#pragma once

//#include <memory>
#include <iostream>
//#include <string>
//#include <vector>

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
          TestClass(int aIntval, float aFloatval);
          TestClass(const TestClass& aOther);
          TestClass& operator= (const TestClass& aOther);

          size_t length() const {return m_length;}
          void resize();
        private:
        // set value as default
        size_t m_length=5;
        int m_intVal=0;
        float m_floatVal=0.f;
        short* m_arrayofShort=nullptr;
    };
} 