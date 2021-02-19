#pragma once

// Reference: http://blog.smartbear.com/c-plus-plus/c11-tutorial-introducing-the-move-constructor-and-the-move-assignment-operator/

// Testing the C++11 move ctor
// A move constructor looks like this:
// A typical move constructor definition would look like this:
// C::C(C&& other); //C++11 move constructor
// 
// It doesn’t allocate new resources. Instead, 
// it pilfers other‘s resources and then sets 
// other to its default-constructed state.
// The move constructor is much faster than a copy 
// constructor because it doesn’t allocate memory 
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
// 	Pilfer other‘s resource.
// 	Set other to a default state.
// 	Return *this.
//
namespace vs15
{
	class MemoryPage
	{
		size_t m_size;
		char * m_buf;
	public:
		explicit MemoryPage(int sz = 512);
		~MemoryPage();

		//typical C++03 copy ctor and assignment operator
		MemoryPage(const MemoryPage&);
		MemoryPage& operator=(const MemoryPage&);

		// typical C++11 move ctor 
		MemoryPage( MemoryPage&& other); //C++11 move ctor
		MemoryPage& operator= ( MemoryPage&& other);//C++11 move assignment operator
	};
} // End of  namespace