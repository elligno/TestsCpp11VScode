#include <iostream>
#include "myMoveClass.h"

using namespace vs15;

MemoryPage::MemoryPage( int sz/*=512*/) 
: m_size(sz), 
  m_buf( new char[m_size])
{
	std::cout << " We are in the MemoryPage ctor\n";
}

MemoryPage& MemoryPage::operator= ( const MemoryPage& aOther)
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

MemoryPage::MemoryPage( const MemoryPage& aOther)
{
	m_size = aOther.m_size;
	m_buf = aOther.m_buf;
}

// C++11 move ctor
MemoryPage::MemoryPage( MemoryPage&& other) 
: m_size(0), 
  m_buf(nullptr)
{
	// pilfer other’s resource
	m_size = other.m_size;
	m_buf = other.m_buf;

	// reset other
	other.m_size = 0;
	other.m_buf = nullptr;
}

MemoryPage& MemoryPage::operator= (MemoryPage&& other)
{
	//C++11
	if (this != &other)
	{
		// release the current object’s resources
		delete[] m_buf;
		m_size = 0;
		
		// pilfer other’s resource
		m_buf = other.m_buf;
		m_buf = other.m_buf;
		
		// reset other
		other.m_buf = 0;
		other.m_buf = nullptr;
	}
	return *this;
}

MemoryPage::~MemoryPage()
{
	delete[] m_buf;
}