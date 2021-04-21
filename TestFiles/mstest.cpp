#include <memory> // smart pointer
#include <vector>
#include <string>


// int fiabonk() {
//     int n, t1 = 0, t2 = 1, nextTerm = 0;

//     // cout << "Enter the number of terms: ";
//     // cin >> n;

//    // cout << "Fibonacci Series: ";

//     for (int i = 1; i <= n; ++i) {
//         // Prints the first two terms.
//         if(i == 1) {
//             cout << t1 << ", ";
//             continue;
//         }
//         if(i == 2) {
//             cout << t2 << ", ";
//             continue;
//         }
//         nextTerm = t1 + t2;
//         t1 = t2;
//         t2 = nextTerm;
        
//         cout << nextTerm << ", ";
//     }
//     return 0;
// }
// class Date;
// class TradeClass 
// {
//   bool isBuy();
//   bool isSell()
//   int nbBuy;   
//   Date dateOfSettle; 
// }

// bool checkShort( int h0, TradeClass trades[], TradeClass newtrade)
// {
  // check the balance
//   if (newTrade.isSell())
//   {
//       int newBalance=0
//   for (size_t i = 0; i < nbTrades; i++)
//   {
//       newBalance += trade[i].nbBuy - newtrade.nbBuy;     
//   }
//   if (h0<0)
//   {
//       return false;
//   }
  
     
//    // return true/false
// }


// int nbPermutation( std::string aStr, int len)
// {
//     //nbPermj = n-1;
//     static count=0;
//     static string glue;
//     beg =  aStr.end();
//     reachEnd = aStr.end();
//     for( size_t i = aStr.begin(); i < aStr.end(); i++)
//     {    
//       do
//       {
//           //glue.append(*begin);
//           auto nextChar = char[i];
//           firstChar = nextChar;
//           *begin = nextChar; 
//           count += 1;
//       } while(reachEnd);

//       //len=len-1
//       start+=begin; // next 
//     }
//     //recursive
//     nbPermutation( string(begin+1,lend), len);
// }

namespace vs11 
{
    void someMS(int* aX)
    {
        // modify the object 
      //  *aX = 2;

        int* w_aa = new int(12);
        *aX = *w_aa;
    }

    void someSharedPtr( std::shared_ptr<int> aX)
    {
        *aX = 3;
    }

    void someUniqPtr( std::unique_ptr<int> aX)
    {
        *aX = 3;
    }
}