#pragma once

// C++ include
#include <iostream>

namespace vs11 
{
    class Bond 
    {
        public:
        Bond() {std::cout << "Default Bond ctor\n";}
        virtual ~Bond() {std::cout << "Bond dtor\n";}
    };
    class MuniBond : public Bond 
    {
        public:
        double Yield() {return 2.6;}
    };
    class TreasuryBond : public Bond 
    {
        public:
        double PriceToYield() {return 3.;}
    };
    class CorporateBond : public Bond 
    {
        public:
        double Coupon() {return 1.2;}
    };

    // class Bus 
    // {
    //   public: // protected cannot be accessed Bus::Driver
    //     class Driver
    //     {
    //         public:
    //         std::string m_name;
    //     };
    //   public:
    //     static Driver* createDriver()
    //     { return new Driver();}
    //   private:
    //     int seats;
    // };

    // class Base { 
    //     public:
    //     void func() {std::cout << "Base class func() method\n";}
    // };
    // class Derived : public Base 
    // {
    //     public:
    //     void func() {std::cout <<}
    // }

} // End of namespace