
#include <ranges> // c++20 feature
#include <vector>
#include <algorithm>

namespace cpp20 
{
    void rngFunc()
    {
        namespace rng = std::ranges;
        namespace vws = std::views;

        std::vector w_vec2rng{1,2,3,4,5};
        // testing both algo sort and take
        std::ranges::sort(std::views::reverse(w_vec2rng) | std::views::take(2));
        
        // print values of sorted range in reverse order

      //  std::ranges::range<std::vector<int>>(w_vec2rng);

     //   std::ranges::range w_rngofVec {w_vec2rng.cbegin(), w_vec2rng.cend()};

    }
} // End of namespace