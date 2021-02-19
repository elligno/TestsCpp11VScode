
#pragma 

#include <memory>   // shared_ptr

namespace aa 
{
  // Some explanation is required:
  // Test to do will be to try to add it in a stl container.
  // Need a copy ctor (copy constructible), by using shared_ptr ...
  // Reference: article of ...
  class testPimpl 
  {
  public:
    // default ctor
    testPimpl();

    // pimpl idiom (shared pointer for incomplete type)
    // copyable and assignable (incomplete type in stl container)
    class testPtrImpl;
    std::shared_ptr<testPtrImpl> m_ptrImpl;
  protected:
  private:
  };
} // End of  namespace