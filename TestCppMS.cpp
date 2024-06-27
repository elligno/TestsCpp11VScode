#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <array>


//using namespace std;

namespace vs15 {
 
// The cost of a stock on each day is given in an array, 
// find the max profit that you can make by buying and selling in those days. 
// For example, if the given array is {100, 180, 260, 310, 40, 535, 695}, 
// the maximum profit can earned by buying on day 0, selling on day 3. 
// Again buy on day 4 and sell on day 6. If the given array of prices is sorted
// in decreasing order, then profit cannot be earned at all.

// Naive approach: A simple approach is to try buying the stocks and selling 
// them on every single day when profitable and keep updating the maximum profit so far.

// Function to return the maximum profit that can be made after buying and
// selling the given stocks.
int maxProfit( int price[], int start, int end)
{
    // If the stocks can't be bought
    if( end <= start)
        return 0;
 
    // Initialise the profit
    auto profit = 0;
 
    // The day at which the stock must be bought
    for( auto i = start; i < end; i++) {
 
        // The day at which the stock must be sold
        for( auto j = i + 1; j <= end; j++) {
 
            // If byuing the stock at ith day and
            // selling it at jth day is profitable
            if( price[j] > price[i]) {
 
                // Update the current profit
                int curr_profit = price[j] - price[i]
                                  + maxProfit(price, start, i - 1)
                                  + maxProfit(price, j + 1, end);
 
                // Update the maximum profit so far
                profit = std::max( profit, curr_profit);
            }
        }
    }

    return profit;
}
  
// Driver code
int testMaxProfit()
{
    int price[] = { 100, 180, 260, 310, 40, 535, 695 };

    int n = sizeof(price) / sizeof(price[0]);
 
    std::cout << maxProfit( price, 0, n - 1);
 
    return 0;
}

// Efficient approach: If we are allowed to buy and sell only once, then we can use following algorithm. 
// Maximum difference between two elements. Here we are allowed to buy and sell multiple times. 
// Following is algorithm for this problem.
// Find the local minima and store it as starting index. If not exists, return.
// Find the local maxima. and store it as ending index. If we reach the end, set the end as ending index.
// Update the solution (Increment count of buy sell pairs)
// Repeat the above steps if end is not reached.

// C++ Program to find best buying and selling days
using namespace std;
 
// This function finds the buy sell
// schedule for maximum profit
void stockBuySell(int price[], int n)
{
    // Prices must be given for at least two days
    if (n == 1)
        return;
 
    // Traverse through given price array
    auto i = 0;
    while (i < n - 1) {
 
        // Find Local Minima
        // Note that the limit is (n-2) as we are
        // comparing present element to the next element
        while ((i < n - 1) && (price[i + 1] <= price[i]))
            i++;
 
        // If we reached the end, break
        // as no further solution possible
        if (i == n - 1)
            break;
 
        // Store the index of minima
        auto buy = i++;
 
        // Find Local Maxima
        // Note that the limit is (n-1) as we are
        // comparing to previous element
        while ((i < n) && (price[i] >= price[i - 1]))
            i++;
 
        // Store the index of maxima
        auto sell = i - 1;
 
        cout << "Buy on day: " << buy
             << "\t Sell on day: " << sell << endl;
    }
}
 
// Driver code
int buyAndSell()
{
    // Stock prices on consecutive days
    int price[] = { 100, 180, 260, 310, 40, 535, 695 };
    int n = sizeof(price) / sizeof(price[0]);
 
    // Fucntion call
    stockBuySell(price, n);
 
    return 0;
}
 
// Time Complexity: The outer loop runs till I become n-1. 
// The inner two loops increment value of I in every iteration. 
// So overall time complexity is O(n)

// This is code is contributed by rathbhupendra
//Output: 

//Buy on day : 0   Sell on day: 3
//Buy on day : 4   Sell on day: 6

    // array = 12,13,14,11,8,7,10,11,8,6 
    // 
    //stock{}

    // int mxProf( std::array<int,10> aPrice) 
    // {
    //    // cmp 
    //    auto max = 0; // current 
    //    auto buy=0;
    //    auto sell=0;
    //    for( auto i = 0; i < aPrice.size()-1;++i)
    //    {
    //        buy+1; // add stock
    //        // diff = array[i+1] - array[i];
    //        for( size_t j = 1; j < 10; j++)
    //        {
    //           auto diff = aPrice[i] - aPrice[j];
              
    //           if( diff > max)
    //           {
    //              max = diff;
    //           }
    //        }//for-loop
    //        auto maxProf = max;
    //        max=0;
    //    }//for-loop

    //    return max;
    // }

template<typename T> class stack
{
    void push( const T& aElem);
    void push( T&& aElem) noexcept;
    bool pop();    
    size_t size() const noexcept {return 0;}
    const T& top() const { return m_data.front();}
          T& top() { return m_data.front();}
    void emplace( const T& aElem);
    private:
      std::deque<T> m_data;
};

} // End of namespace
