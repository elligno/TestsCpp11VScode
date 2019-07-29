
#include <iostream>
#include "Classes/Class2Test.h"

namespace vs11 
{
    void testJean()
    { 
        std::cout << "test Batch file multiple lines compile\n";
    }
    void usesBus()
    {
      //  Bus::Driver* w_driver =  Bus::createDriver();
      Widget const *cw = new Widget; // pointer constant
      // Widget* w = cw; cannot be done because const T* cannot be used to initialize 
      Widget* w = const_cast<Widget*>(cw); // this fix can be used to initialize it
    }
}