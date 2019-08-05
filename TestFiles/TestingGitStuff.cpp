// C++ includes
#include <memory>
#include <iostream>
// STL includes
#include <list>
#include <vector>
#include <algorithm>
// Package includes
#include "../myClass.h"
#include "../Classes/Class2Test.h"

namespace vs11 
{
    // Some test usage 
    // Create a pointer to animal and then pass it to the function
    // after calling the function 
    void testSomeStuff(Animal* aPet)
    {
        // smart pointer
        std::unique_ptr<Animal> w_myPet( new Animal);
        w_myPet->setName("Jean Pet");
        std::unique_ptr<Animal> w_yourPet;
        w_yourPet = std::move(w_myPet);
        // now myPet is usable anymore (from move semantic)
        // w_myPet->geNmae() will not work

        w_myPet.reset(aPet);
        // set name again
        w_myPet->setName("another pet");

        // at the end of this function aPet will have the name "Another Name"
    }

    // testing some factory method with C++11
    // using the move semantic to create method factory
    std::unique_ptr<TestClass> createTestClass()
    {
        return std::unique_ptr<TestClass>(new TestClass);
    }
    
    void testUnitTest() {std::cout  << "Unit testing its bread and butter\n";}

    void stlTest()
    {
        std::unique_ptr<TestClass> w_mvClass =  createTestClass();

        // create alist and i want to remove 4
        // method remove not available with vector
        // for this reason we need to use the stl algorithm remove
        std::list<int> w_listRem = {1, 2, 3, 4, 4, 4, 5, 4, 6, 7, 8, 9};
        std::list<int>::size_type w_checkSiz = w_listRem.size();
        std::cout << "Size of the original list:" << w_checkSiz << "\n";
        // removing element
        w_listRem.remove(4);           // remove all 4 or the first one
        w_checkSiz = w_listRem.size(); // size is now 8
        std::cout << "Size of the original list:" << w_checkSiz << "\n";

        // let say i want to erase a value from the list, size still the same
        auto w_foundIt = std::find(w_listRem.cbegin(), w_listRem.cend(), 8);
        if (w_foundIt != w_listRem.cend())
        {
            w_listRem.erase(w_foundIt);
        }
        w_checkSiz = w_listRem.size();

        std::vector<int> w_vecIt = {1, 2, 3, 4, 5, 6, 7, 8};
        auto w_foundInVec = std::find(w_vecIt.cbegin(), w_vecIt.cend(), 4);
        if (w_vecIt.cend() != w_foundInVec)
        {
            w_vecIt.erase(w_foundInVec);
        }
        auto w_vecSiz = w_vecIt.size();
        auto w_remValItpos = std::remove(w_vecIt.begin(), w_vecIt.end(), 6);
        w_vecSiz = w_vecIt.size();
        for (const auto &w_val : w_vecIt)
        {
            std::cout << "Value is :" << w_val << "\n";
        }
    }
} // End of namepsace
