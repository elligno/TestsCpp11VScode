#include <vector>
#include "../Classes/Class2Test.h"
#include "BondClass.h"
#include "TemplatedClass.hpp"

namespace vs11 
{
    // C++11 alias templates
    template<class T> using vec = std::vector<T>;
    template<typename T> using myGeneric = T;

    // old stuff enum, now can declare with class key word
    // what is the main dofference between old style and the new one.
    // First new one  
    enum REG
    {
        stocks,
        bonds
    };
    enum LTC
    {
        swaps,
        swaptions
    };
    enum DRV
    {
        futures,
        options
    };

    void testEnum()
    {
        // Which are valid operations?
        REG team1;
    //    LTC team2;
    //    DRV team3;

        // team2=1;  not valid cannot assign an int
        //team3=options+futures; not valid cannot assigned int to DRV
        team1 = bonds;
        
        // team1=futures; not valid cannot asign DRV to REG
        team1 = stocks;
   }

   void testClassBond()
   {
       // which correctly execute each of unique functionnality?
       CorporateBond b1, *cp; 
       TreasuryBond  b2, *tp;
       MuniBond b3, *mp;

       Bond* w_bonds[3] { &b1,&b2,&b3 };
       Bond *bp;
       double uniqueValue;

       for(int i=0;i<3;++i)
       {
           // add line of code here (these are the one that execute unique functionality of each class)
           bp = w_bonds[i];
           mp = dynamic_cast<MuniBond*>(bp);
           if(mp) uniqueValue = mp->Yield();
           cp = dynamic_cast<CorporateBond*>(bp);
           if(cp) uniqueValue = cp->Coupon();
           tp = dynamic_cast<TreasuryBond*> (bp);
           if(tp) uniqueValue = tp->PriceToYield();

     // doesn't work because incompatible type
     //      mp = dynamic_cast<TreasuryBond*>(bp);
     //      if(mp) uniqueValue = mp->Yield();
       }
   }

   void protocol(vs11::JeanTest *aType)
   {
       std::cout << "We have the following: " << aType->getType() << aType->getVolume() << "\n";
   }

   void testBindMechanism()
   {
       std::cout << "Some basic test about virtual binding\n";
       vs11::JeanTest w_jTest;
       vs11::Volume1 w_vol1;
       vs11::Volune2 w_vol2;
       // call our function
       protocol(&w_jTest);
       protocol(&w_vol1);
       protocol(&w_vol2);

       // some test abut static variable 
       // Note in the main function it doesn't compile, just don't know why??
 //      vs11::SomeClass objSome;
   //    int check = objSome::data;
    //    int check1 = vs11::SomeClass::data;
   }

   void testBase()
   {
       Derived objDerived;
       // calling func() of base class through an instance of derived
       // i did not we could do that!!
       objDerived.Base::func();

       // Alias test
       typedef int alias;
       alias myAlias=9;
       // template alias
       vec<float> myVector;
       myVector.push_back(1);
       myVector.push_back(3);

       myGeneric<int> age;
       age=2;
   }

   std::string getCity(bool c)
   {
       if(c) return "Chicago";
       else return "New York";
   }
   void printCity( const std::string& aCity)
   {
       std::cout << "We are in the printCity\n";
   }
   void printCity( std::string&& aCity)
   {
       std::cout << "printCity mv function\n"; 
   }
   void testMvCall()
   {
       std::string city = getCity(false);
       printCity(city);
       printCity(getCity(true));
   }

   void testInitialization()
   {
       // NOTE all data initialized with ctor () means init with zero value
       // otherwise they are not initialized or put some weird value
       struct historyStudent 
       {
           int id;
           float gpa;
       };

       // templated function
       fun(1,2.0,"bukle my shoe");
       fun("silly string");
       fun(1,2,3,4,5);
      // fun({1,2,3,4,5});

       char* arrChar = new char[100]; // 100 bytes on the free store
       std::cout << "Byte allocated on the heap is: " << sizeof(arrChar) << "\n";
       char* charAllocated = (char*)malloc(100); // what we do here?
       std::cout << "Byte allocated on the heap is: " << sizeof(charAllocated) << "\n";
       char* sizOf = (char*)malloc(100*sizeof(char));  //      
       std::cout << "Byte allocated on the heap is: " << sizeof(sizOf) << "\n";

       float* beginningsalary = new float();
       std::cout << *beginningsalary << "\n";
       float* endingSalary = new float;
       std::cout << *endingSalary << "\n";

       int* feet = new int[10]();
       std::cout << feet[0] << " " << feet[4] << " " <<feet[6] <<"\n";
       
       int* inches = new int[10];
       std::cout << *inches << "\n";
       std::cout << inches[0] << " " << inches[4] << " " << inches[6] <<"\n";

       historyStudent* student1 = new historyStudent;
       std::cout << student1->id << " " << student1->gpa  << "\n";
       historyStudent* student2 = new historyStudent();  
       std::cout << student2->id << " " << student2->gpa  << "\n";
   }
} // End of namespace 