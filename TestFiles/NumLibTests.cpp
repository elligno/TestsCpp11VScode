// C include
#include <cassert>
// C++ include
#include <iostream>
// boost range iterator library includes
#include <boost/range/iterator_range.hpp>    // range iterator lib 
// Numeric library includes
#include "jb_scalarField.h" // include grid lattice
#include "Elgo_Ptr.hpp" // in house smart pointer impl
#include "PhysCte.h" // some physical constant

namespace SfxType 
{
    // In the old days of C++ there was no way to optimize this out: 
    // returning heavy-weight objects by value was simply a no-go. 
    // Fortunately in C++11 and greater we are allowed (and encouraged) 
    // to do this, by implementing class with move semantics. In a nutshell, 
    // we will steal existing data from temporary objects instead of making 
    // useless clones. Don't copy, just move, because moving is always cheaper.
    // just testing the return value construct (move semantic)
    SfxNum::scalarField getScalarField()
    {
        // return by value
        return SfxNum::scalarField{ std::shared_ptr<SfxNum::gridLattice> {}, std::string {}};
    }

    /**
     * @brief Some tests numerical library types. 
     *  I've been using these types for many years 
     *  but not sure i really understand what's going 
     *  on behind the hood. Also, it would be nice to 
     *  adpapt to modern C++ (e.g. move ctor to improve efficency).  
     * 
     */
    void testScalarField() 
    {
        //
        // Testing our library (numeircal basic type)
        //

        // Base numerical library type
        std::cout << "Test linking with BaseNumTypes library\n";
        const double test = basenum::PhysicalConstant::sGravity;
        std::cout << "Gravity value is: " << test << "\n";

        // create a grid with E. McNeil discretization (dx=0.1, x0=0, xN=10)
        // Node index from i=1,..,10 mean dx=0.1
        // using auto keyword to keep simple notation and easier to read
        // 10 grid nodes from i= 1,...,10 and x = 0.,...,1. result dx=0.1
        auto w_grid = // E McNeil discretization as default (construct from string)
            std::make_shared<SfxNum::gridLattice>( std::string( "d=1 [0,1] [1:10]"));

        // checking some values (x=0.)
        const auto checkXmin = w_grid->xMin(1); //one dimensional
        auto checkXmax = w_grid->xMax(1);       //no need
        const auto w_dx = w_grid->Delta(1);
        const auto w_baseIdx = w_grid->getBase(1); // first dimension
        assert( 0.1 == w_dx);

        // create a scalar field for testing our VSCode environment
        std::shared_ptr<SfxNum::scalarField> w_U1 { new SfxNum::scalarField{ w_grid, std::string("A")}};
        const std::string w_fieldName = w_U1->name();
        if( !w_fieldName.empty())
        {
            std::cout << "Field name is : " << w_fieldName << "\n";
        }

        auto w_nbPtsTotal = w_grid->getNoPoints();
        assert( 10 == w_nbPtsTotal);

        double* myRealArray = new double[w_nbPtsTotal] {}; // initalization to zero (call default ctor)
        // sanity check about iniitialization
        assert( 0. == myRealArray[0]);
        assert( 0. == myRealArray[1]);
        assert( 0. == myRealArray[5]);

        // create a real array to initialize the scalarField
        // Reminder: numerical array indexing element from 1,..,N
       SfxNum::RealNumArray<double>* w_realArray = 
           new SfxNum::RealNumArray<double> { w_nbPtsTotal, myRealArray};
        w_U1->values(*w_realArray); // takes the ownership

        // call two-dimensional array indexing (i,j)
        // but here we consider the one-dimensional case
        std::cout << w_realArray << "\n"; // just a check
#if 0         
        // method added to print values in the one-dimensinal case
        w_realArray.print1D(std::cout); // bug: print N-1 element
        std::cout << "Size of the array is: " << w_realArray.size() << "\n";

        // copy initalization (could be done with move semantic),
        // but for now not supporte dfor numerical array
        const SfxNum::RealNumArray<double> w_cpyRealArr = w_realArray;
        assert( w_realArray.size(1) == w_cpyRealArr.size(1));

        // checking default values of our scalar field (must be zero)
        const SfxNum::RealNumArray<double> &myValArray = w_U1->values();
       
        // pair of iterator (Note::since we have declared a const RealArray
        // we have to create a const iterator, in this case "const double*")
        using iter_rng = boost::iterator_range<const double *>;
        iter_rng w_iterRealArray { myValArray.getPtr(), myValArray.getPtr() + myValArray.size(1)};
        //boost::make_iterator_range( myValArray.getPtr(),myValArray.getPtr()+myValArray.size(1));
        std::copy( w_iterRealArray.begin(), w_iterRealArray.end(),
                  std::ostream_iterator<double>(std::cout, "\n"));
          
        std::cout; // print values copied in cout 

#endif
        // do some clean-up avoid leak
     //   delete[] myRealArray;
#if 1        
        using gridLatticePtr = std::shared_ptr<SfxNum::gridLattice>;
        gridLatticePtr w_gridTest { new SfxNum::gridLattice{}}; // two dimensional grid as default
        auto w_scalarfieldPtr = 
             std::make_shared<SfxNum::scalarField>( gridLatticePtr { new SfxNum::gridLattice{}}, std::string("myScalar"));

        // copy construct test and check shared_ptr
       // SfxNum::scalarField w_Ufield{ gridLatticePtr{}, std::string("U Field")}; 
        SfxNum::scalarField w_Ucpy = *w_U1; // check count of shared_ptr for grid and values (default copy ctor)
        *w_scalarfieldPtr = w_Ucpy; // assignment ctor
        auto w_nbGridVal = w_scalarfieldPtr->values().size(); // shall be equal to 10
        auto w_checkType = w_scalarfieldPtr->values(); // return a ref to RealNumArray&
        w_checkType(1) = 1.; // auto type deduction
        auto w_nbDim = w_scalarfieldPtr->values().getDimenions();

        std::cout << "Array values are: "; 
        w_checkType.print1D( std::cout);

        // initalize smart pointer empty  
        std::shared_ptr<SfxNum::scalarField> w_scalarFptr {nullptr}; //direct list initalization
        auto w_nbCount = w_scalarFptr.unique(); //use_count == 1 
        w_scalarFptr.reset( new SfxNum::scalarField { w_gridTest, std::string("Test smart")});
        w_scalarFptr = w_U1; // assignment smart pointer (copy scalarField)
#endif
        std::cout << "Leaving test numerical stuff\n";
    }
} // End of namespace