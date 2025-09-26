
#include "vectorField.h"

namespace SfxType 
{
    vectorField::vectorField( std::shared_ptr<Sfx::gridLattice1D>& aGrid, std::string aName)
    : m_name{std::move(aName)},
      m_U1{nullptr},
      m_U2{nullptr}
      {
          if( nullptr == m_U1)
          {
              m_U1.reset( new Sfx::scalarField1D( aGrid,std::string("U1")));
          }
          if( nullptr==m_U2)
          {
              m_U2.reset( new Sfx::scalarField1D( aGrid,std::string("U2")));
          }
          
          std::cout << "Creating a vector field " << m_name << std::endl;
      }

    vectorField::vectorField( std::shared_ptr<Sfx::scalarField1D>& aU1, 
		std::shared_ptr<Sfx::scalarField1D>& aU2, std::string aName)
    : m_name(std::move(aName)),
      m_U1(aU1),
      m_U2(aU2)
     {
          std::cout << "vectorField ctor from scalarFiled" << std::endl;
     }
} // End of namespace