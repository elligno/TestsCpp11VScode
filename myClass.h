#pragma once

namespace vs1 
{
    // This is the bsae class for all tyoe of our testing environment
    // We are just experienting some OO consepts 
    class Object  // abstract base class
    {
        public:
        Object()=default;
        Object(const Object& aOther)=delete;
        Object& operator= (const Object& aOther)=delete;

        virtual bool equals(Object& aOther)=0;
        virtual bool isAbstract() {return true;}
    };
    
    class myClass : public Object
    {
        public:
        explicit myClass(unsigned aUint);

        // services
        void printSelf();
    };
} // End of namespace