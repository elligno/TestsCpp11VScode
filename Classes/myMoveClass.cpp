#include <iostream>
#include "myMoveClass.h"

using namespace vs15;

MemoryPage::MemoryPage(int sz /*=512*/)
	: m_size(sz),
	  m_buf(new char[m_size])
{
	std::cout << " We are in the MemoryPage ctor\n";
}

MemoryPage &MemoryPage::operator=(const MemoryPage &aOther)
{
	// check for self-assignment
	if (this != &aOther)
	{
		if (m_buf) // release resource
		{
			delete m_buf;
			m_buf = nullptr;
			m_size = 0;
		}

		// allocate new resource
		m_buf = new char[aOther.m_size];
		m_size = aOther.m_size;
	}
	return *this;
}

MemoryPage::MemoryPage(const MemoryPage &aOther)
{
	m_size = aOther.m_size;
	m_buf = aOther.m_buf;
}

// C++11 move ctor
MemoryPage::MemoryPage(MemoryPage &&aOther) noexcept
: m_size(0),
  m_buf(nullptr)
{
	std::cout << "In MemoryPage(MemoryPage&&). size = "
			  << aOther.m_size << ". Moving resource." << std::endl;
#if 0
	// pilfer other's resource
	m_size = other.m_size;
	m_buf = other.m_buf;

	// Release the data pointer from the source object so that
    // the destructor does not free the memory multiple times
	other.m_size = 0;
	other.m_buf = nullptr;
#endif
	//
	*this = std::move(aOther);
}

MemoryPage &MemoryPage::operator= ( MemoryPage &&aOther) noexcept
{
	std::cout << "In operator=(MemoryPage&&). length = "
			  << aOther.m_size << "." << std::endl;

	// no operation if you try to assign the object to itself.
	if (this != &aOther)
	{
		// free any resources (such as memory) from the object that is being assigned to
		// release the current object's resources
		delete[] m_buf;
		m_size = 0;

		// Copy the data pointer and its length from the source object
		// pilfer other's resource
		m_size = aOther.m_size;
		m_buf = aOther.m_buf;

		// Release the data pointer from the source object so that
		// the destructor does not free the memory multiple times
		aOther.m_size = 0;
		aOther.m_buf = nullptr;
	}
	return *this;
}

MemoryPage::~MemoryPage()
{
	delete[] m_buf;
}

MemoryBlock::MemoryBlock(size_t length)
: _length(length),
  _data(new int[length])
{
	std::cout << "In MemoryBlock(size_t). length = "
			  << _length << "." << std::endl;
}

MemoryBlock::~MemoryBlock()
{
	std::cout << "In ~MemoryBlock(). length = "
			  << _length << ".";

	if (_data != nullptr)
	{
		std::cout << " Deleting resource.";
		// Delete the resource.
		delete[] _data;
	}

	std::cout << std::endl;
}

MemoryBlock::MemoryBlock(const MemoryBlock &other)
: _length(other._length),
  _data(new int[other._length])
{
	std::cout << "In MemoryBlock(const MemoryBlock&). length = "
			  << other._length << ". Copying resource." << std::endl;

	std::copy(other._data, other._data + _length, _data);
}

MemoryBlock &MemoryBlock::operator=(const MemoryBlock &other)
{
	std::cout << "In operator=(const MemoryBlock&). length = "
			  << other._length << ". Copying resource." << std::endl;

	if (this != &other)
	{
		// Free the existing resource.
		delete[] _data;

		_length = other._length;
		_data = new int[_length];
		std::copy(other._data, other._data + _length, _data);
	}
	return *this;
}

MemoryBlock::MemoryBlock( MemoryBlock &&other) noexcept
: _data(nullptr), 
  _length(0)
{
	std::cout << "In MemoryBlock(MemoryBlock&&). length = "
			  << other._length << ". Moving resource." << std::endl;

	// Copy the data pointer and its length from the
	// source object.
	_data = other._data;
	_length = other._length;

	// Release the data pointer from the source object so that
	// the destructor does not free the memory multiple times.
	other._data = nullptr;
	other._length = 0;
}

MemoryBlock& MemoryBlock::operator= ( MemoryBlock&& other) noexcept
{
   std::cout << "In operator=(MemoryBlock&&). length = "
             << other._length << "." << std::endl;

   if( this != &other)
   {
      // Free the existing resource.
      delete[] _data;

      // Copy the data pointer and its length from the
      // source object.
      _data = other._data;
      _length = other._length;

      // Release the data pointer from the source object so that
      // the destructor does not free the memory multiple times.
	  //  otherwise destructor of "other" frees stolen memory
      other._data = nullptr;
      other._length = 0;
   }

   return *this;
}