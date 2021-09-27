
#pragma once

// C++ includes
#include <memory> // smart pointer
#include <string>
#include <valarray>
#include <algorithm>
#include <functional>
// boost include
#include <boost/operators.hpp>
// App include
#include "gridLattice.h"

namespace vs11 
{
	/**
	 * @brief scalarField based on std numerical container for fast floating point operation.
	 *    Type that represent a function over a grid in a finite difference approximation.
	 *    std valarray support modern C++ move semantic as well math operation supported 
	 *    by such a function. 
	 */
    class valarrField : public boost::addable<valarrField> // operator+
    {
 	public:
		/**
		 * @brief Construct a field lattice form a grid
		 * 
		 * @param grid finite difference grid
		 * @param fieldname name description 
		 * @return 
		 */
		valarrField( std::shared_ptr<gridLattice>& grid, 
			         std::string fieldname);

        /**
         * @brief Construct a new valarr Field object
         * 
         * @param aOther 
         */
	    valarrField( const valarrField& aOther)=default;
		/**
		 * @brief Assign new valarr field object
		 * 
		 * @param aOther 
		 * @return valarrField& 
		 */
		valarrField& operator= (const valarrField& aOther)=default;

		// move semantic support

		/**
		 * @brief Move copy construct
		 * 
		 * @param aOther other field to construct from
		 */
        valarrField( valarrField&& aOther)=default;

		/**
		 * @brief Move assignment construct
		 * 
		 * @param aOther other field to construct from
		 * @return valarrField& new created field  
		 */
        valarrField& operator= ( valarrField&& aOther)=default;

		/**
		 * @brief Enable access to grid-point values
		 * 
		 * @return std::valarray<double>& 
		 */
		      std::valarray<double>& values()        { return *m_gridPointValues; }
		const std::valarray<double>& values() const  { return *m_gridPointValues; }

		/**
		 * @brief Enable access to the grid
		 * 
		 * @return gridLattice& 
		 */
		       gridLattice& grid()                   { return *m_gridLattice; }
		const gridLattice& grid() const              { return *m_gridLattice; }

        /**
         * @brief Field name description
         * 
         * @return std::string 
         */
		std::string name() const                     { return m_fieldName; }

		/**
		 * @brief Set the values of the field
		 * 
		 * @param aNewArray 
		 */
		void values( std::valarray<double>& aNewArray);
        
		/**
		 * @brief Unary negate operator
		 * 
		 * @return valarrField 
		 */
		valarrField operator- () const
		{ 
			std::valarray<double> w_retArray(m_gridPointValues->size());
			std::transform( std::begin(*m_gridPointValues), std::end(*m_gridPointValues), 
			     std::begin(w_retArray), std::negate<double> {});

			valarrField w_retField = *this;
			w_retField.values(w_retArray);

			return w_retField;
	    }

		/**
		 * @brief Unary plus operator
		 * 
		 * @return valarrField 
		 */
        valarrField operator+ () const { return *this; }

        /**
         * @brief Math operation on field (add 2 field)
         * 
         * @param aOther 
         * @return vector field
         */
        valarrField& operator+= ( const valarrField& aOther)
		{ 
			*m_gridPointValues += aOther.values();
			return *this;
		}

        /**
         * @brief 
         * 
         * @param aOther 
         * @return valarrField& 
         */
		valarrField& operator-= ( const valarrField& aOther)
		{
			return *this += -aOther;
		}

        /**
         * @brief 
         * 
         * @param aOther 
         * @return valarrField& 
         */
		valarrField& operator*= ( const valarrField& aOther);

     //   valarrField operator+ ( const valarrField& aOther);
      private:
        std::shared_ptr<gridLattice>           m_gridLattice;     /**<  */
        std::shared_ptr<std::valarray<double>> m_gridPointValues; /**<  */
		std::string                            m_fieldName;       /**<  */
    };

} // End of namespace