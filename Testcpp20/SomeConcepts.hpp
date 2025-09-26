
#pragma once 

#include <tuple>
// Cpp20 includes
#include <span>      // C++20 view
#include <ranges>    // C++20 range
#include <utility>
#include <concepts>

namespace cpp20 
{
    // Usage 
    //    std::cout << std::apply(myFunc2Apply, std::pair(1, 2)) << '\n';
    // myFunc2Apply can be a closure, a callable
    template <typename... Ts>
    std::ostream &operator<<( std::ostream &os, const std::tuple<Ts...> &theTuple)
    {
        std::apply(   // Func to apply and parameter pack expansion
            [&os](Ts const &...tupleArgs)  
            {
                os << '[';
                std::size_t n{0};
                ((os << tupleArgs << (++n != sizeof...(Ts) ? ", " : "")), ...);
                os << ']';
            },
            theTuple);
        return os;
    }

    template <typename T>
    struct testmyRng_t : T
    {
        // i don't think that's the right way to use it!!
        // i think its a variable that user have to set,
        // make the container as a view, but not sure!!  
        // T must inherit from view_interface i guess???
 //       std::ranges::enable_view<testmyRng_t> = true;
       // std::ranges::take_while_view(r,f) f a predicate to mark the end
        using T::begin;
        using T::end;

        testmyRng_t() {}
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
            //std::views::range_size(rrng);  size range
            // concept
            std::ranges::sized_range<aRng>;
        }

        return true;
    }

    template<typename T>
    requires( std::ranges::bidirectional_range<T>)
    auto passSTLrng(T aRng)
    {
        // std::vector jean b  of E, McNeil algo
    }

    // pass args by value, not sure if its the right things to do
    // i'm really not sure about that!!
    void myRngFunc( std::ranges::input_range auto aRng)
    {
        // some utility for code cleaning
        namespace rng = std::ranges;
        namespace vws = std::views;
        
        static_assert(rng::range<aRng>); // sanity check

        // let's try some new stuff
    }

    // To ensure that a function takes sequence where you cannot 
    // modify the elements, require const container returns an iterator
    // to const elements (N. Josuttis, C++20 page 310)
    template<typename T>
    void ensureReadOnlyElementAccess( const T& coll)
    requires std::is_const_v<std::remove_reference_t<decltype(*coll.begin())>>
    {
        // ....
    }

    // can be used with range and span 
    template<typename T>
    void print(const T& aT)
    {
        // check if it is a contiguous range, span need contiguous range
        // similar to subrange, but don't need range made from to have 
        // or support iterator, only need to have a function data() that
        // return the raw pointer (span is cheap to copy)
        if constexpr (std::ranges::contiguous_range<T>) // concept of continuous rng
        {}
    }
} // End of namespace