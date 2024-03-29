// C++ includes
#include <iostream>
#include <memory> // smart pointer
#include <vector>
#include <string>
#include <algorithm>
#include <array>
#include <set>


int fiabonk() 
{
    int n, t1 = 0, t2 = 1, nextTerm = 0;

    // cout << "Enter the number of terms: ";
    // cin >> n;

   // cout << "Fibonacci Series: ";

    for (int i = 1; i <= n; ++i) {
        // Prints the first two terms.
        if(i == 1) {
            std::cout << t1 << ", ";
            continue;
        }
        if(i == 2) {
            std::cout << t2 << ", ";
            continue;
        }
        nextTerm = t1 + t2;
        t1 = t2;
        t2 = nextTerm;
        
        std::cout << nextTerm << ", ";
    }
    return 0;
}

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
  bool has4( int aNumber)
  {
    while( aNumber != 0)
    {
      // debugging purpose set to 4
      if( aNumber%10 == 4) //  rest of division
      {
        /* code */
        return true;
      }
      aNumber = aNumber/10; //promote to integer
    }
    return false;
  }

  void countingDigit( int start=1, int end=500)
  {
    auto result = 0;
    // set to 500 for testing
    for( auto i = 0; i < 500; ++i)
    {
      /* code */
      result += has4(i) ? 1 : 0;
    }

    std::cout << "Number of digit is: " << result << "\n";
  }

  // Remider: pointer is pass by value, all modification of the 
  // pointer is made to the copy (local)  
  void ptrPassVal( int* aX)
  {
    int *w_aa = new int(12);
    aX = w_aa; // modify pointed-to (change copy)
  }

  void ptrPassRef( int*& aX)
  {
    int *w_aa = new int(12);
    aX = w_aa; // ok now point to new address
  }

  void ptrPassMod( int* aX)
  {
    // modify the object
    *aX = 18;
  }

  // good question, what do i think
  void someSharedPtr( std::shared_ptr<int> aX)
  {
    // what do we do here? pointed-to
    auto w_ptd2Auto = *aX;

    // this is the pointer owned by the shared pointer 
    auto* w_ptrFromShrd = aX.get();
    
    // re-use of auto type
    decltype(w_ptd2Auto) w_var = 2;
   
    std::cout << "Type of shared ptr is: " << typeid(w_ptd2Auto).name() << "\n";

    *aX = 3;
  }

  void someSharedPtrRef( std::shared_ptr<int>& aX)
  {
    auto checkCount = aX.use_count();
    *aX = 3;
  }

  void validateMStest()
  {
    int* w_val2Pass = new int(2);
    ptrPassVal( w_val2Pass);
    std::cout << "Pointer value is : " << *w_val2Pass << "\n";

    ptrPassRef( w_val2Pass);
    std::cout << "Pointer value is : " << *w_val2Pass << "\n";

    ptrPassMod( w_val2Pass);
    std::cout << "Pointer value is : " << *w_val2Pass << "\n";

    auto w_valFromShr = std::make_shared<int>(65);
    someSharedPtr( w_valFromShr); // still 65 because work on copy (pass-by-value) NO!!! modify pointed-to
    std::cout << "Pointer value is : " << *w_valFromShr << "\n";

       // count when pass by ref? increment it?
    auto w_valFromShrRef = std::make_shared<int>(5);
    someSharedPtrRef( w_valFromShr); // 
    std::cout << "Pointer value is : " << *w_valFromShr << "\n";

    // number of 4
    countingDigit();

    std::cout << "Finished ms test\n";
  }

  struct historyStudent
  {
    // default ctor
    int id;
    float gpa;
  };

  // call default ctor to zero initialization 
  void CtorInit()
  {
    float* beginningSalary = new float{}; // default ctor call init to zero
    float* endingSalary    = new float;   // uninitialized

    int* feet   = new int[10](); // zero initilization ok!
    int* inches = new int[10];   // no, uninitialized

    historyStudent* student1 = new historyStudent;    // both member unitialized
    historyStudent* student2 = new historyStudent {}; // both member initialized to 0

    delete beginningSalary;
    delete endingSalary;
    delete[] feet;
    delete[] inches;
    delete student1;
    delete student2;
  }

  // MS interview questions  
  void someDuplicateTest()
  {
    std::vector<int> w_vecOrg { 1,3,8,4,5,3,1,8};
    std::vector<int> w_vecUniq { 1,3,8,4,5,3,1,8};
    std::sort( w_vecUniq.begin(), w_vecUniq.end());
    
    //std::vector<int> w_cpyVec;
    //w_cpyVec.reserve(10);
  //  auto endIter = std::unique( w_vecUniq.begin(), w_vecUniq.end());
   // std::copy( std::unique( w_vecUniq.begin(), w_vecUniq.end()), w_vecUniq.end(), std::back_inserter(w_cpyVec));
  //  w_cpyVec.shrink_to_fit();
  //  auto zizV = w_cpyVec.size();
    w_vecUniq.erase( std::unique( w_vecUniq.begin(), w_vecUniq.end()), w_vecUniq.end());
  //   auto w_vecSiz = w_vecUniq.size();
    // assert(5==w_vecSiz);  // 3 elements duplicate
    if( w_vecOrg.size() != w_vecUniq.size())
    {
        auto numDupl = w_vecOrg.size() - w_vecUniq.size();
        std::vector<int> w_duplElem; // direct list initializer {8} 1 elem set to 8 
        w_duplElem.reserve(numDupl);   // be carefull when declaring vector
        auto w_countDupl = 0;
        for( size_t i = 0; i < w_vecOrg.size(); i++)
        {
           auto numDup = std::count( w_vecOrg.begin(), w_vecOrg.end(), w_vecOrg[i]);
           if(numDup>1 && w_countDupl<4) 
           { 
               w_duplElem.push_back(w_vecOrg[i]);}
               ++w_countDupl; if(w_countDupl==3) break;
        }
        for( auto i = 0; i < w_duplElem.size(); i++)
        {
            std::cout << "Duplicate elem " << w_duplElem[i] << std::endl; 
        }
    }//if

    //std::cout << "New end eleme : " << *endIter << std::endl;

    const int price[] = { 100, 180, 260, 310, 40, 535, 695 };
    auto maxElem = price[0];
    auto numElem = sizeof(price)/sizeof(price[0]);
    for( auto i=1; i<numElem; ++i) // find greatest one
    {
        if( price[i] > maxElem)
        {
           maxElem = price[i];
        } 
    }

    std::vector<int> w_vecInt{std::begin(price),std::end(price)};
    std::sort( w_vecInt.begin(),w_vecInt.end());    
  //  std::sort( std::begin(price),std::end(price));

    vs11::validateMStest();
  }

   // MS interview questions (simplest way to find duplicate is to use set)
   // I think the question was: having 2 sequences of number find duplicate
   // or number that are in both sequence. Abopve i use some STL algorithms
   // such as sort, unique and erase, but the simpliest way to do it is the following.
  void findDuplicateTest()
  {
    std::array<int,10> w_arr1 { 1,2,3,3,4,7,1,4,5,6};
    std::array<int,10> w_arr2 { 1,2,3,4,3,2,7,7,8,9};

    std::set<int> w_sortedRng1( w_arr1.cbegin(), w_arr1.cend()); // unique element
    std::set<int> w_sortedRng2( w_arr2.cbegin(), w_arr2.cend()); // unique element

    std::vector<int> w_vecUniq; w_vecUniq.reserve(10);
    std::set_intersection( w_sortedRng1.cbegin(), w_sortedRng1.cend(),
                           w_sortedRng2.cbegin(), w_sortedRng2.cend(), std::back_inserter(w_vecUniq));

    w_vecUniq.shrink_to_fit();

     std::cout << "The following number are duplicate in both sequence\n";

     for( auto val : w_vecUniq)
     {
       std::cout << val << std::endl;
     }

     // Can i do it with STL algorithm such as sort, unique and erase, i do think so     
     std::vector<int> w_sortArr1{ w_arr1.cbegin(), w_arr1.cend()};
     std::vector<int> w_sortArr2{ w_arr2.cbegin(), w_arr2.cend()};
     std::sort( w_sortArr1.begin(), w_sortArr1.end()); 
     std::sort( w_sortArr2.begin(), w_sortArr2.end());

     // sanity check
     if( std::is_sorted( w_sortArr1.cbegin(),w_sortArr1.cend()))
     {
       w_sortArr1.erase( std::unique( w_sortArr1.begin(), w_sortArr1.end()), w_sortArr1.cend());
     }
     if( std::is_sorted( w_sortArr2.cbegin(),w_sortArr2.cend()))
     {
       w_sortArr2.erase( std::unique( w_sortArr2.begin(), w_sortArr2.end()), w_sortArr2.cend());
     }

     std::vector<int> w_mergeSortVec; w_mergeSortVec.reserve(10);
     std::merge( w_sortArr1.begin(),w_sortArr1.end(),
         w_sortArr2.begin(),w_sortArr2.end(), std::back_inserter(w_mergeSortVec));

     //std::set_intersection();
 
    // std::vector<int> w_testAlgo; w_testAlgo.reserve(10);
    // std::copy( std::unique( w_sortArr1.begin(), w_sortArr1.end()), 
    //            w_sortArr1.cend(), std::back_inserter(w_testAlgo));

     auto w_siz1 = w_sortArr1.size();
     w_sortArr1.erase( std::unique( w_sortArr1.begin(), w_sortArr1.end()), w_sortArr1.cend());
     auto w_siz2 = w_sortArr1.size();
     w_sortArr2.erase( std::unique( w_sortArr2.begin(), w_sortArr2.end()), w_sortArr2.cend());

    std::vector<int> w_mergeSortVec1; w_mergeSortVec1.reserve(10);
     std::merge( w_sortArr1.begin(),w_sortArr1.end(),
         w_sortArr2.begin(),w_sortArr2.end(), std::back_inserter(w_mergeSortVec1));

    w_mergeSortVec1.shrink_to_fit();

    // we need to remove duplicate or to check duplicate
    
     // remove all duplicate
  }
} // End of namespace