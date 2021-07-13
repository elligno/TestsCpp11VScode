#pragma once

// C++ includes
#include <iostream>
#include <memory>
#include <string>

namespace vs11
{
    /**
     * @brief ... to be completed
     * 
     */
    class JeanTest
    {
        public:
        virtual int getVolume() { return 0;}
        char getType() const    { return 'R';}
    };
    class Volume1 : public JeanTest
    {
        public:
        int getVolume() override { return 50;}
        char getType() const     { return 'V';}
    };
    class Volune2 : public JeanTest
    {
        public:
        int getVolume() override {return 150;}
        char getTYpe() const     {return 'S';}
    };
     class StaticVarTest
    {
        public:
        static int m_sVar;
    };

    class Driver; // forward declarartion
    class Bus 
    {
      public: // protected cannot be accessed Bus::Driver
        class Driver
        {
            public:
            std::string m_name;
        };
      public:
        static Driver* createDriver()
        { return new Driver();}
      private:
        int seats;
    };

    class Widget
     {
         public:
         void createIt() { std::cout << "Widget creator\n";}
     };

     class move_only 
     {
         private:
         std::unique_ptr<Widget> m_data;
         public:
         move_only()=default;
         move_only( const move_only&)=delete;
         move_only( move_only&& aOther)
         : m_data(std::move( aOther.m_data))
         {
         }     
         move_only& operator= (const move_only&)=delete;
         move_only& operator= ( move_only&& aOther)
         {
            m_data = std::move( aOther.m_data);
            return *this;
         }
    };
    /**
     * @brief 
     * 
     */
     class SomeClass
     {
         public:
         // cannot do that because checkStatic is not static and call by a static method
         // in this case no this pointer is pass implictly as argument to the method, then
         // we cannot reference a data member (this->checkStatic)
         //static void callNonStatic() {std::cout << checkStatic << "\n";}
         int checkStatic;
         static int data;

         SomeClass() = default;
         SomeClass( const SomeClass& aOther);            //copy ctor
         SomeClass& operator= (const SomeClass& aOther); //assignment ctor

         static int getStaticVar() {return data;}
     };
     class Base
     {
         public:
         void func() { std::cout << "Base::func()\n";}
     };
     class Derived : public Base
     {
         public:
         void func() { std::cout << "Derived::func()\n";}
     };
     class Animal
    {
        public:
        Animal() {m_position=0;}
        void changePosition(int i) {m_position+=i;}
        // not using referene semantic
        void setName(std::string aName) {m_name=aName;}
        std::string getName() const {return m_name;}
        private:
        int m_position;
        std::string m_name;
    };
    class WalkingAnimal : virtual public  Animal
    {
        public:
        void move() {changePosition(2);}
    };
    class SwimmingAnimal : virtual public  Animal
    {
        public:
        void move() {changePosition(1);}
    };
    class Penguin : public WalkingAnimal, public SwimmingAnimal
    {
        public:
        void swim()
        {
            // move(); ambiguous call (diamond problem)
            Animal::changePosition(2);
            SwimmingAnimal::move();
        }
        void walk() {}
    };
} // End of namespace