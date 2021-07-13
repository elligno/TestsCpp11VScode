#pragma once

// C++ include
#include <memory> // smart pointer
// Numeric library includes
#include "jb_scalarField.h" // include grid lattice#include "valarrField.h"

namespace SfxType 
{
    /**
     * @brief Testing some concept of vector field 
     *  In the prototyping use a pair of shared_pointer of scalarField.
	 *  We need a type with methods that act or represent of vector field
	 *  of component ... to be completed
	 *  Pair of smart pointer doesn't say much, we need to wrap a class
     */
	class vectorField 
	{
	  public:
	     /**
	      * @brief Construct a new vector Field object (two-components vector).
	      * 
		  *   Contains state variables of the physical system.
	      */
	     vectorField() = default;

		 /**
		  * @brief Construct a new vector Field object (copy ctor)
		  *
		  * @return aOther vector to initialize from
		  */
		 vectorField( const vectorField& aOther) = default;

		 /**
		  * @brief assigment ctor
		  * 
		  * @return aOther vector to initialize from
		  */
		 vectorField& operator= ( const vectorField& aOther)=default;

	    /**
	     * @brief Construct a new jb vectorField object
	     * 
	     * @param aGrid one-dimensional grid over which field is defined 
	     * @param aName name representation of vector field
	     */
		vectorField( std::shared_ptr<SfxNum::gridLattice>& aGrid, std::string aName);
		
		/**
		 * @brief 
		 * 
		 * * @param aU1 a scalar field pointer
	     *   @param aU2 a scalar field pointer
		 */
		vectorField( std::shared_ptr<SfxNum::scalarField>& aU1, 
		std::shared_ptr<SfxNum::scalarField>& aU2, std::string aName);

        /**
         * @brief Construct a new vector field object (move semantic)
         * 
         * @param aName string representation of the vector field
         */
		vectorField( vectorField&& aOther)
	    : m_name{ std::move(aOther.m_name)},
		  m_U1{ std::move(aOther.m_U1)},
		  m_U2{ std::move(aOther.m_U2)}
		  {
			  std::cout << "vectorField copy move ctor\n";
		  }

        // move semantic ctor??

		/**
		 * @brief return name description of the vector field 
		 * 
		 * @return const std::string& 
		 */
        const std::string& name() const { return m_name; }

		/**
		 * @brief Return component of vector field (by value)
		 * 
		 * @return std::shared_ptr<SfxNum::scalarField
		 */
        SfxNum::scalarField getU1() const { return *m_U1; }
		SfxNum::scalarField getU2() const { return *m_U2; }

       // not sure about these methods
		// startIndex()
		// endIndex()
		// min()
		// max()
	  private:
        std::string m_name;
		std::shared_ptr<SfxNum::scalarField> m_U1;
		std::shared_ptr<SfxNum::scalarField> m_U2;
	};
} // End of namespace