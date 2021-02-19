
#include <iostream>

namespace cpp11 
{
  enum class testEnum11 
  {
    algo1=0,
    algo2=1
  };

  enum class MyEnum
  {
    rk2=1,
    rk4=2
  };

  void enumFunc(testEnum11 aEnum)
  {
    std::cout << "Enumerator test\n";

    testEnum11 wEnum = testEnum11::algo1;
    if (wEnum == aEnum)
    {
      std::cout << "we have 2 enumerator that are the same\n";
    }
    else
    {
      std::cout << "We have 2 enumerator thatr are not equal\n";
    }
  }

  void testEnum11()
  {
    // new enumerator is just great
    enumFunc(testEnum11::algo1);
    enumFunc(testEnum11::algo2);
  }
} // End of namespace
