
// C++ includes
#include <string>
#include <iostream>
// STL includes
#include <list>
#include <vector>
#include <algorithm>

// delaring some global function or variables
namespace vs11
{
    void testToAddFile();
    void testingShardPtr();    
}

// =======================================================
//
//               Windows main entry point
//
// =======================================================
int main()
{
    std::cout << "Starting debugging with VSCode\n";

    // not sure i do understand the difference between them 
    int ii={}; // what swe do exactly? call a ctor?
    int jj = int();
    int kk;
    
    // create alist and i want to remove 4 
    // method remove not available with vector
    // for this reason we need to use the stl algorithm remove
    std::list<int> w_listRem = {1,2,3,4,4,4,5,4,6,7,8,9};    
    std::list<int>::size_type w_checkSiz = w_listRem.size();
    std::cout << "Size of the original list:" << w_checkSiz << "\n";
    // removing element
    w_listRem.remove(4); // remove all 4 or the first one 
    w_checkSiz = w_listRem.size(); // size is now 8
    std::cout << "Size of the original list:" << w_checkSiz << "\n";
    
    // let say i want to erase a value from the list, size still the same 
    auto w_foundIt = std::find(w_listRem.cbegin(),w_listRem.cend(),8);
    if(w_foundIt != w_listRem.cend()) {w_listRem.erase(w_foundIt);}
    w_checkSiz = w_listRem.size();

   std::vector<int> w_vecIt = {1,2,3,4,5,6,7,8};
   auto w_foundInVec = std::find( w_vecIt.cbegin(), w_vecIt.cend(),4);
   if( w_vecIt.cend() != w_foundInVec)
   {w_vecIt.erase(w_foundInVec);}
   auto w_vecSiz = w_vecIt.size();
   auto w_remValItpos =  std::remove(w_vecIt.begin(),w_vecIt.end(),6);
   w_vecSiz = w_vecIt.size();
  for( const auto& w_val : w_vecIt)
  {
      std::cout << "Value is :" << w_val << "\n"; 
  }

  //vs1::testingShardPtr();
//    vs1::testToAddFile();
    
    std::cout << "Hello World!";
}