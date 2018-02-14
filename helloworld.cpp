
//// C++ include
#include <iostream>

// delaring some global function or variables
namespace vs1 
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
    
    vs1::testingShardPtr();
//    vs1::testToAddFile();
    
    std::cout << "Hello World!";
}