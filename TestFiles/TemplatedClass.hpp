#pragma once 

// C++ include
#include <iostream>

namespace vs11 
{
    template<class T, class ... Args>
    void fun( const T& first, const Args& ... rest)
    {
        std::cout << "Implementing variadic template\n";
    }
} // End of namespace