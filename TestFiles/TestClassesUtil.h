
#pragma once

// c++ includes
#include <iostream>
#include <memory> // smart pointer
#include <string>

namespace cpp11 
{
  class MusicProduct 
  {
  public:
    MusicProduct( const std::string& aName) : m_name(aName) {}
    virtual void play()=0;
    virtual void displayTitle()=0;
  protected:
    std::string m_name;
  };

  class Cassette : public MusicProduct 
  {
  public:
    Cassette( const std::string& aName) : MusicProduct(aName) {}
    void play() override         { std::cout << "Playing cassette\n";}
    void displayTitle() override { std::cout << "Title is " << "My Cassette Title" << "\n";} 
  };

  class CD : public MusicProduct 
  {
  public:
    CD( const std::string& aName) : MusicProduct(aName) {}
    void play() override { std::cout << "Playing CD\n";}
    void displayTitle() override { std::cout << "Title is: " << "My CD title is " << "\n";}
  };

  // Class use to test and experiment the shared pointer
  class TestShrPtr 
  {
  public:
    // default ctor (test if it is called with make_shared)
    TestShrPtr()
    {
      // some memory allocation
      m_ptr2val = new float[5];
      m_shrptrVal = std::make_shared<float>();
    }
    TestShrPtr( std::shared_ptr<float> aValues) { std::cout << "Shared Ptr ctor\n";     }
    TestShrPtr( const TestShrPtr& aOther)       { std::cout << "TestShrPtr copy ctor\n";}
    ~TestShrPtr() 
    { 
      std::cout << "We are in the TestShrPtr dtor\n";
      if( m_ptr2val)
      {
        delete [] m_ptr2val;
        m_ptr2val=nullptr;   // nullptr is a type
      }
    }

    // just a method to test
    void setFloatVal() {}
    void printFloatVal() {}

    // some methods (smart ptr as argument) value
    // Usage:
    // ------
    //   shared_ptr w_px1();
    //   testPassArg(w_px1); // do something with shared ptr 
    //  Don't do that, read Scott Meyers about auto_ptr in 
    //  his book "More Effective C++"
    //  Reason why is simple!! i am not sure
    void testPassArg( std::shared_ptr<float> aArg) 
    {
      // if we change the smart pointer does it affect ... 
      std::cout << "Pass shared ptr by value\n";
      // create a copy of the shared ptr
      std::shared_ptr<float> w_localShr=aArg;
      // now let's change some attribute

      std::cout << "We are leaving the testPassArg() function\n";
    }

    // pass smart ptr as ref 
    // Usage:
    // ------
    //   shared_ptr w_px1();
    //   testPassArg(w_px1); // do something with shared ptr
    void testPassRefArg( std::shared_ptr<float>& aArg) 
    {
      // if we change the smart pointer does it affect ...
      std::cout << "Pass shared ptr by reference\n";
    }
    // pass smart ptr as const ref 
    // Usage:
    // ------
    //   const shared_ptr w_px1();
    //   testPassArg(w_px1); // do something with shared ptr
    //   std::ref can i use it?? in this situation
    void testPassRefArg( const std::shared_ptr<float>& aArg) 
    {
      // if we change the smart pointer does it affect ...
      std::cout << "Pass shared ptr by const reference\n";
    }
  protected:
  private:
    float m_val; 
    float* m_ptr2val;
    std::shared_ptr<float> m_shrptrVal;
  };
} // End of namespace