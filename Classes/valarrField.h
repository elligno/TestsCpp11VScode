
#pragma once

// C++ includes
#include <memory> // smart pointer
#include <string>
#include <valarray>
// App include
#include "gridLattice.h"

namespace vs11 
{
    class valarrField 
    {
 	public:
		// make a field from a grid and a fieldname
		valarrField( std::shared_ptr<gridLattice>& grid, 
			        std::string fieldname);

		// enable access to grid-point values
		      std::valarray<double>& values()        { return *m_gridPointValues; }
		const std::valarray<double>& values() const  { return *m_gridPointValues; }

		// enable access to the grid
		       gridLattice& grid()                   { return *m_gridLattice; }
		const gridLattice& grid() const              { return *m_gridLattice; }

		std::string name() const                     { return m_fieldName;}

		// set the values of the field  
	//	void values( RealNumArray<real>& new_array);
        
        // some operations
        valarraField& operator+= ( const valarraField& aOther);

      private:
        std::shared_ptr<gridLattice>           m_gridLattice;
        std::shared_ptr<std::valarray<double>> m_gridPointValues;
		std::string                            m_fieldName;
    };
} // End of namespace