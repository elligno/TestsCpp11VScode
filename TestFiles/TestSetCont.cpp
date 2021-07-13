#pragma once

#include <iostream>
#include <string>
#include <set>

namespace vs11 
{
    /**
     * @brief Class to test some set feature C++11
     * 
     */
    class Person {
        public:
        Person( std::string aFirstName, std::string aLastName) 
        : m_firstName( std::move(aFirstName)),
          m_lastName( std::move(aLastName))
          {}
          auto firstName() const -> std::string {return m_firstName;}
          auto lastName() const -> std::string {return m_lastName;}
        private:
        std::string m_firstName;
        std::string m_lastName;
    };

    // bool operator< ( const Person& aPerson1, const Person& aPerson2)
    // {
    //     return aPerson1.firstName() < aPerson2.firstName();
    // }
    void checkBasics()
    {
       std::cout << "Basics test with set\n";

       auto personCmp = [] ( const auto& aPerson1, const auto& aPerson2)
       {
           return aPerson1.firstName() < aPerson2.firstName();
       };

       // create a set of person with comparer
       std::set<Person, decltype(personCmp)> w_setPerson {personCmp};
    }
}// End of namespace