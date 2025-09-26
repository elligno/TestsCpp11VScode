#include <iostream>
#include <ranges> // c++20 feature
#include <vector>
#include <algorithm>

// include form our testing environment
// #include "SomeConcepts.hpp" // basic function that uses std::views and range

namespace cpp20
{
    // NOTE: I think I took that from N. Josuttis book "C++20 The Complete Guide"
    // declaring a function with auto (equivalent to a template, not sure)
    // but i think it is, need to do a double check
    void print(auto&& rng)
    {
        //  would like to check for type and value category of the passed argument
        // Reminder: decltype can be used in 2 different way:
        //  decltype(var) and decltype((var)) the former return the type 
        // and the latter the value category
        auto checkVType = std::is_same_v<decltype(rng),std::pair<double,double>>;
        // double parenthesis for value category!!! lvalue reference
        auto checkVCategory = std::is_same_v<decltype((rng)),std::pair<double,double>&>;

        // can I do that? check range concept
        if constexpr ( std::ranges::range<decltype(rng)>)
        {
            std::cout << "we have a range!!!\n";
        }
        
        // structured binding C++17 (this only work for range of pair, isn't?)
        // like a map or a vector of pair?
        for( auto [key, value] : rng)
        {
            std::cout << "Key is: " << key << "Value is: " << value << "\n";
        }
    }

    // functin to be forwarded
    void Func2Fwd(int aInt, float aFloat) 
    {
        std::cout << "Forwarded function with 2 args\n";
    }

    // perfect forwarding function uysing universal reference
    // void fwdFunc(auto&& aFunc2Fwd)
    // {
    //     return std::forward<aFunc2Fwd>; ??? don't get it?
    // }

    void rngFunc()
    {
        namespace rng = std::ranges;
        namespace vws = std::views;

        std::vector w_vec2rng{1, 2, 3, 4, 5, 6,7,8,9,10,11,12,13,14,15};
        // testing both algo sort and take
        rng::sort(std::views::reverse(w_vec2rng) | std::views::take(2));
        rng::copy(std::views::reverse(w_vec2rng) | std::views::filter([](int aInt2Filtr){return aInt2Filtr%2;}) |std::views::take(3), 
        std::ostream_iterator<int>{std::cout, "\n"});
        std::cout;
        
        // print values of sorted range in reverse order

        //  std::ranges::range<std::vector<int>>(w_vec2rng);
        // NOTE this wrong, don't use like that. First range is concept
        //  we are not creating a range!! to create a range from
        // a container you have to use the factory/adaptor such as
        //  counted(), all(), ... and other.
        auto viewRng = vws::all(w_vec2rng);       // convert a range to a view
        if (std::ranges::view<decltype(viewRng)>) // check if it is view (cheap to copy)
        {
            //  not sure what all return, but it depends if we pass
            // an lvalue, rvalue or a range (ref_view for this case)
            // what is a ref_view, does it have a reference semantic?  
            std::cout << "We have a view which is a range C++20\n";
        }

        //   std::ranges::range w_rngofVec {w_vec2rng.cbegin(), w_vec2rng.cend()};
    }
} // End of namespace