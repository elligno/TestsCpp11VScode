#pragma once

// C++ include
#include <memory> // smart pointer
// Numeric library include
#include "Sfx/Sfx_scalarField1D.h" // include grid lattice#include "valarrField.h"

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
		// vectorField( const vectorField& aOther) = default;

		 /**
		  * @brief assigment ctor
		  * 
		  * @return aOther vector to initialize from
		  */
	//	 vectorField& operator= ( const vectorField& aOther)=default;

	    /**
	     * @brief Construct a new jb vectorField object
	     * 
	     * @param aGrid one-dimensional grid over which field is defined 
	     * @param aName name representation of vector field
	     */
		vectorField( std::shared_ptr<Sfx::gridLattice1D>& aGrid, std::string aName);
		
		/**
		 * @brief 
		 * 
		 * * @param aU1 a scalar field pointer
	     *   @param aU2 a scalar field pointer
		 */
		vectorField( std::shared_ptr<Sfx::scalarField1D>& aU1, 
		std::shared_ptr<Sfx::scalarField1D>& aU2, std::string aName);

        /**
         * @brief Construct a new vector field object (move semantic)
         * 
         * @param aName string representation of the vector field
         */
		// vectorField( vectorField&& aOther)
	    // : m_name{ std::move(aOther.m_name)},
		//   m_U1{ std::move(aOther.m_U1)},
		//   m_U2{ std::move(aOther.m_U2)}
		//   {
		// 	  std::cout << "vectorField copy move ctor\n";
		//   }

		// NOTE don't need to define a move ctor, if scalar field 
		// is moveable it will apply to every member of the field.
		// scalar field has no copy ctor, but Copy Elison is mandatory
		// since C++17 (problem move ctor is user defined, which shouldn't be)
		// Check VS2022 project NumTypes library and do more tests!!!
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
        Sfx::scalarField1D getU1() const { return *m_U1; }
		// doesn't compile because dereference to get the scalar field
		//  and since return by copy it moves??? maybe but not sure!! 
		// message: cannot be dreferenced because it is a deleted function.
		//SfxNum::scalarField getU2() const { return *m_U2; }
		
		//std::shared_ptr<SfxNum::scalarField> getU1shr() const {return m_U1;}

       // not sure about these methods
		// startIndex()
		// endIndex()
		// min()
		// max()
	  private:
        std::string m_name;
		std::shared_ptr<Sfx::scalarField1D> m_U1;
		std::shared_ptr<Sfx::scalarField1D> m_U2;
	};
} // End of namespace