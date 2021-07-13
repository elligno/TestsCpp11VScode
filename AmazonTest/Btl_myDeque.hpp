
//  Author: Jean Belanger
//  Date of creation: February 22, 2012
//  Revision history:

#ifndef btlmydeuqe_H
#define btlmydeuqe_H

// stl includes
#include <vector>
#include <algorithm>

namespace Btl 
{
	//
	// An implementation of deque container
	//
	template<typename T /*data type*/>
	class myDeque
	{
	public:
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		myDeque(unsigned aSize=10) 
		: m_numElems(0),     // empty
		  m_capacity(aSize), // initial capacity
		  m_incr(10)         // increment value (capacity)
		{
			m_elem=new T[m_capacity]; // fixing initial array size
			m_temp.reserve(m_capacity);
		}
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		~myDeque() 
		{
			if (m_elem)
				delete [] m_elem;
		}
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		void pop_front()
		{
			// remove element from end
			if (m_numElems<=0)
			{
				std::cout << "throw out-of-range exception\n"
			}

			// remove element from start (new range)
			std::vector<T> w_vecFront(&m_elem[0]+1, // one-past-first element
				                      &m_elem[0]+m_capacity);
			// 
			std::copy(w_vecFront.begin(),w_vecFront.end(),&m_elem[0]);
			--m_numElems; // decrement number of element
		}
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		void pop_back()
		{
			// remove element from end
			if (m_numElems<=0)
			{
				std::cout << "throw out-of-range exception\n"
			}
			--m_numElems; // decrement number of element
		}
        // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		void push_front(const T& aElem)
		{
			if (m_numElems==0) // buffer is empty
			{
				m_elem[m_numElems]=aElem;
				++m_numElems;
			}

			// check size (full) need to shift elements
			unsigned w_freePlace=m_capacity-m_numElems;
			if (m_numElems<=w_freePlace)
			{
				if (!m_temp.empty()) // empty the temporary buffer
				{
					m_temp.clear();
				}

				// copy element in a temporary container
				std::copy(&m_elem[0],&m_elem[0]+m_numElems,
					std::back_inserter(m_temp));
				m_elem[0]=aElem; // add the element in front
				++m_numElems;
				// copy back the original element 
				// starting from one-pass-the first element
				std::copy(m_temp.begin(),m_temp.end(),&m_elem[0]+1);
			}
			else // can't shift elements because not enough room
			{
				if (!m_temp.empty()) // empty the temporary buffer
				{
					m_temp.clear();
				}
				// copy original element in temporary buffer
				std::copy(std::copy(&m_elem[0],&m_elem[0]+m_numElems,
					std::back_inserter(m_temp)));

				resize(); // 
				m_elem[0]=aElem; // add the element in front
				++m_numElems;
				// copy back the original element 
				// starting from one-pass-the first element
				std::copy( m_temp.begin(),m_temp.end(),&m_elem[0]+1);
			}   
		}
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		void push_pack(const T& aElem)
		{
           m_elem[m_numElems]=aElem;
		   ++m_numElems;
		}
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		bool empty const {return m_numElems==0;}
		std::size_t size() const {return m_numElems;}
		double& operator[] (unsigned aI)             
		{
			// check for index out-of-range
			if (aI<0 && aI > m_numElems)
			{
				std::cout << "Throw an exception index out-of-range\n";
			}
			return m_elem[aI];
		}
		const double& operator[] (unsigned aI) const 
		{
			// check for index out-of-range
			if (aI<0 && aI > m_numElems)
			{
				std::cout << "Throw an exception index out-of-range\n";
			}
			return m_elem[aI];
		}
	private:
		T* m_elem;             // element type
		unsigned m_incr;       // increment capacity
		unsigned m_numElems;   // number of elements (size)
		unsigned m_capacity;   // memory allocation
		std::vector<T> m_temp;
		resize()
		{
			// need to re-allocate memory to make some room
			if (m_elem)
			{
				delete [] m_elem;
			}
			m_capacity+=m_incr;       // reset capacity 
			m_elem=new T[m_capacity]; // new buffer
		}
	};
} // End of namespace
#endif // Include guard