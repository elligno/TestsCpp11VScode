// just a test to add new file in the vscode project

// C include
#include <cassert>
// C++ includes
#include <iostream>
#include <memory>
// STL includes
#include <vector>
#include <map>

// Need to find a way to add this file 
namespace vs1 
{
    // testing some new features of C++11
    // there is a lot a features which make programming 
    // more enjoyable.
    void testToAddFile()
    {
        std::cout << "Compiling our new added file\n";

        // just checking vector working
        std::vector<int> w_listInit = {1,2,3,4,5};
        size_t w_checkVec = w_listInit.size(); // shall be equal to 5

        int i=2;
        float f=3.141592f;
        // force reference semantic and auto is pair<int&,float&>
        auto w_checkRef = std::make_pair( std::ref(i), std::ref(f));
        std::cout << "Value of i and f are: " << i << " " << f << "\n";

        i=4;
        f=5.23f;
        std::cout << "Value of i and f are: " << i << " " << f << "\n";

        std::cout << "Just about leaving testaddfile function\n";
    }

    void testMapFeatures()
    {
        // this is a very noice feature of C++11, creating alias
        // which make it clear about the intent of the programmer
        using mapofint = std::map<const std::string, int>;

        // create a map with key const to avoid implicit conversion
        // using iniatalizer list ctor
        mapofint w_mapTest = {{"jean",1},{"toutou",2},{"Gisele",3}};

        // let insert new element in our map and check for success
        if( w_mapTest.insert(mapofint::value_type("another",1)).second)
        {
            // ii ma not if itds worth since its not a console app (create logger??) 
            std::cout << "We have inserted an element in the map\n";
        }
    }

    void testingShardPtr()
    {
        using namespace std;

       // it seems that the make_shared call default ctor to ensure
		// that type is constructed completely, not sure but looks like it!! 
		shared_ptr<int> w_testShPtr = make_shared<int>(1);
		int w_checkVal = *w_testShPtr;
		assert(1==w_checkVal);
		// copy another shared ptr
		shared_ptr<int> w_px = w_testShPtr;
		int* w_valx = w_px.get();              // some weird value
		*w_px = 12; // does it change the value of the original pointer
		            // since we have reference semantic??

		// i do expect that both values are equal
		int w_checkOrgVal = *w_testShPtr;
		assert(w_px == w_testShPtr);

		// check count of the smart pointer
		size_t w_checkCount = w_testShPtr.use_count();
		assert( w_testShPtr.use_count()==2); // at creation
		w_checkCount = w_px.use_count();
		assert(2==w_checkCount); // just don't et it

		// set some initial values
		int* w_intPtr = w_testShPtr.get();  // pointer
		assert( w_intPtr != nullptr);
		int w_checkPtr = *w_testShPtr;
		assert(w_checkPtr==12);
		w_checkPtr=2; // it change the shared ptr value??
		              // no, don't see why it should!!

		*w_intPtr = 3; // will it change the value of the smart pointer?
		// check if smart pointer changed
		int w_changed = *w_testShPtr;

		// change it but with pointer
	    assert(*w_testShPtr == 12);
// 		*w_intPtr = 45;  changing smart pointer (object) value
// 		assert(*w_testShPtr.get() == 45);
    }
} // End of namspace