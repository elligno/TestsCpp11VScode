
#pragma once 

// Cpp20 includes
#include <ranges>
#include <concepts>

namespace cpp20 
{
    template<typename T>
    struct testmyRng_t : T
    {
        using T::begin;
        using T::end;

        testmyRng() {}
    };

    void print() {}

    // generic function new feature of c++20 uisng concept
    template<typename T>
    auto genFunc( const std::same_as<T> auto& aCls)
    {
        return 1.;
    }

    // use concept as param  (E. McNeil hll algo impl)
    template<typename T>
    requires (std::is_pointer_v<T>) // only pointer 
    auto passPtrArg(T aRng) 
    {
        static_assert( !std::ranges::range(aRng));
        if constexpr ( !std::ranges::input_range(aRng)) // read only
        {
            std::ranges::range_size(rrng); // size range
        };

        return true;
    }

    template<typename T>
    requires( std::ranges::bidirectional_range<T>)
    auto passSTLrng(T aRng)
    {
        // std::vector jean b  of E, McNeil algo
    }
} // End of namespace