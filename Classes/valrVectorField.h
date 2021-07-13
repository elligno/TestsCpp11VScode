#pragma once

// C++ include
#include <memory>
// Numeric library includes
#include "jb_scalarField.h" // include grid lattice#include "valarrField.h"

namespace SfxType 
{
	// Just prototyping some base type 
	// for our programming environment (just )
#if 0
	/**
	 * @brief Model of a vector of field of two component.
	 * 
	 */
	class vectorField 
	{
		using fieldPtr = std::shared_ptr<jb::scalarField>;
	public:
		// shall we use a default ctor? does it make sense?
		vectorField() = default; // initialize smart pointer to nullptr?
		vectorField( std::string aName);
		
		// shall we have a copy ctor? or default will do
		 
		// shall we have a assignment ctor? or default will do
		
		// what are the base methods?
		
		/**
		 * @brief name of the vector field
		 * 
		 * @return const std::string 
		 */
		const std::string name() const { return m_name;}

		// return field discretization
		const gridLattice& grid() const { return m_U1->grid();}
		
	    /**
	     * @brief 
	     * 
	     * @return std::valarray<real>& 
	     */
		std::valarray<real>& U1values()    { return m_U1->values();}
	
		/**
		 * @brief 
		 * 
		 * @return std::valarray<real>& 
		 */
		std::valarray<real>& U2values()             { return m_U2->values();}
		const std::valarray<real>& U1values() const { return m_U1->values();}
		const std::valarray<real>& U2value() const  { return m_U2->values();}
		
		// return vector component (shall i return it as a reference?)
		std::shared_ptr<valarrField> getU1() const { return m_U1;}
		std::shared_ptr<valarrField> getU2() const { return m_U2;}
	//	std::pair<fieldPtr,fieldPtr> asPair() const    { return std::make_pair(m_U1,m_U2);}

	    // math operations
	private:
		std::string m_name;
		std::shared_ptr<valarrField> m_U1;
		std::shared_ptr<valarrField> m_U2;
	};
#endif // vector field valarray