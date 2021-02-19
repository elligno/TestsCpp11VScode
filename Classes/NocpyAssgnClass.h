#pragma once

namespace vs15 
{
	// NOTE: very important to read the Book of Anthony Williams
	// "C++ Concurrency in Action" Appendix A, 
	// "Brief reference for some C++11 languages features"
	// It's a must before start usingt C++11 new features 
	// such as constant-expression which is reallly not clear in my mind.
	// Also all the rvalue and move semantic
	//
	class NocpyAssgnClass 
	{
	public:
		// what default, the meaning of it? not so sure!!
		NocpyAssgnClass() = default;
		
		// using constant expression, means evaluated at compile time
		constexpr NocpyAssgnClass(unsigned aInt,float aFloat) 
		: m_uint32(aInt),m_flt32(aFloat) {}

		// Note: don't need to do that i mean to make it private
		// by adding the keyword delete we ensure that copy and 
		// assignment are prohibited on client side

		// copy ctor
		NocpyAssgnClass( const NocpyAssgnClass& aOther) = delete;
		NocpyAssgnClass& operator= ( const NocpyAssgnClass& aOther) = delete;

		// Some helper function for testing
		// Note: cannot declare in the cpp file, because if we declare 
		// as a constant expression
		constexpr float getFloat32() const { return m_flt32; }
		void addFloat(const float aFloat);
	private:

		// don't need to initialize it in the ctor, no duplicate initialization
		const unsigned m_uint32 = 23;
		float m_flt32 = 2.1f;
	};

} // End of namespace
