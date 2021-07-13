#pragma once

#include <vector>
#include <iostream>

// Reference: http://blog.smartbear.com/c-plus-plus/c11-tutorial-introducing-the-move-constructor-and-the-move-assignment-operator/

// Testing the C++11 move ctor
// A move constructor looks like this:
// A typical move constructor definition would look like this:
// C::C(C&& other); //C++11 move constructor
// 
// It doesn't allocate new resources. Instead, 
// it pilfers other's resources and then sets 
// other to its default-constructed state.
// The move constructor is much faster than a copy 
// constructor because it doesn't allocate memory 
// nor does it copy memory buffers.
//
// A move assignment operator has the following signature:
// 
// C& C::operator=(C&& other);//C++11 move assignment operator
// 
// A move assignment operator is similar to a copy constructor 
// except that before pilfering the source object, it releases 
// any resources that its object may own. The move assignment 
// operator performs four logical steps:
// 
// Release any resources that *this currently owns.
// 	Pilfer other's resource.
// 	Set other to a default state.
// 	Return *this.
//
namespace vs15
{
	/**
	 * @brief Class that implement the move ctor semantic  
	 *  
	 *  A move constructor enables the resources owned by an rvalue object to be moved into an lvalue without copying.
	 *  A move constructor looks like this:
     *  A typical move constructor definition would look like this:
     *  C::C( C&& other); //C++11 move constructor
     *
     *  It doesn't allocate new resources. Instead, it pilfers other's resources and then sets 
     *  other to its default-constructed state. The move constructor is much faster than a copy 
     *  constructor because it doesn't allocate memory nor does it copy memory buffers.
	 */
	class MemoryPage
	{
		size_t m_size; /**< */
		char * m_buf;  /**< */
	public:
		/**
	     * @brief Construct a new Memory Page object
	     * 
	     * @param sz
	    */
		explicit MemoryPage(int sz = 512);

		/**
	     * @brief Destroy the Memory Page object
	     * 
	    */
		~MemoryPage();

		/**
	     * @brief Construct a new Memory Page object
	     * 
	    */
		MemoryPage(const MemoryPage &);

		/**
	     * @brief Assignment ctor
	     * 
	     * @return MemoryPage& 
	    */
		MemoryPage &operator=(const MemoryPage &);

		// typical C++11 move ctor

		/**
	     * @brief Construct a new Memory Page object (//C++11 move ctor)
	     * 
	     * @param other object to be moved
	    */
		MemoryPage(MemoryPage &&other) noexcept;
		MemoryPage &operator=(MemoryPage &&other) noexcept; //C++11 move assignment operator
	};

	//  Robust Programming (move ctor implementation)
    //   To prevent resource leaks, always free resources (such as memory, file handles, and sockets) in the move assignment operator.

    //   To prevent the unrecoverable destruction of resources, properly handle self-assignment in the move assignment operator.

    //   If you provide both a move constructor and a move assignment operator for your class, you can eliminate redundant code 
    //   by writing the move constructor to call the move assignment operator. The following example shows a revised version 
    //   of the move constructor that calls the move assignment operator:
    //   *this = std::move();

class MemoryBlock
{
public:

   /**
    * @brief Simple constructor that initializes the resource.
    * 
    * @param length 
    */
   explicit MemoryBlock(size_t length);
  
   /**
    * @brief Destroy the Memory Block object
    * 
    */
   ~MemoryBlock();
 
   /**
    * @brief Construct a new Memory Block object
    * 
    * @param other 
    */
   MemoryBlock( const MemoryBlock& other);

   /**
    * @brief Copy assignment operator.
    * 
    * @param other 
    * @return MemoryBlock& 
    */
   MemoryBlock& operator= ( const MemoryBlock& other);

   /**
    * @brief / Move constructor.
    * 
    * @param other object to move
    */
   MemoryBlock(MemoryBlock &&other) noexcept;

   /**
    * @brief Move assignment operator.
    * 
    * @param other 
    * @return MemoryBlock& 
    */
   MemoryBlock &operator=(MemoryBlock &&other) noexcept;

   /**
    * @brief  Retrieves the length of the data resource.
    * 
    * @return size_t 
    */
   size_t Length() const
   {
	   return _length;
   }

private:
   size_t _length; // The length of the resource.
   int* _data; // The resource.
};

  /**
   * @brief ...
   * 
   */
  class MoveTest
  {
  public:
    /**
     * @brief default ctor
     * 
     */
    MoveTest() { std::cout << "Default ctor of MoveTest\n";}
    /**
     * @brief Construct MoveTest object from string (value semantic)
     * 
     * @param aStr 
     */
    MoveTest( std::string aStr) : m_str11( std::move(aStr)) 
    {
      std::cout << "MoveTest by string value ctor\n";
    }
    /**
     * @brief Construct a new Test object
     * 
     * @param aOther 
     */
    MoveTest( const MoveTest& aOther) { std::cout << "Copy ctor of MoveTest\n";}
    
    /**
     * @brief Re-assign a  MoveTest object (move semantic)
     * 
     * @param aOther 
     * @return  
     */
    MoveTest( MoveTest&& aOther) noexcept
    : m_str11( std::move( aOther.m_str11)),
      m_vecofInt( std::move( aOther.m_vecofInt))
    { 
      std::cout << "Move ctor of MoveTest\n";
  
      // could do that (use assignment move ctor)
	  //*this = std::move(aOther);
    }
    
    // not sure does it leave  
    MoveTest& operator= ( MoveTest&& aOther) noexcept
    {
      //std::cout << "Assignment Move ctor of MoveTest\n";
       std::cout << "In operator=(MoveTest&&). length = "
                 << aOther.size() << "." << std::endl;

       if( this != &aOther)
       {
         // Free the existing resource.
         //delete[] _data;
         m_str11.clear();
         m_vecofInt.clear();

         // swap content and leave object in a state that is destructible
         m_str11 = std::move( aOther.m_str11);
         m_vecofInt = std::move( aOther.m_vecofInt);

         // do i need to do that? i do think after moving
         // object in a state that it destructible (valid state)
		 // Actually we don't newed to do that, the 2 lines above
		 // we call move ctor for both vector and string, after 
		 // that these objects shall be in valid state 
        // aOther.m_str11.clear();
        // aOther.m_vecofInt.clear();
       }
       return *this;
    }

    void addElem(int aInt) { m_vecofInt.push_back(aInt);}
	std::vector<int>::size_type size() const {return m_vecofInt.size();}
  private:
    std::string m_str11;         /**< test string*/
    std::vector<int> m_vecofInt; /**< test vector*/
  };
} // End of  namespace