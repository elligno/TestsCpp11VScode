
#ifndef sfxguid_H
#define sfxguid_H

// c++ include (not sure)
#include <iosfwd>

namespace Sfx
{
	/// Globally unique identifier used to identify plugin objects for instantiation
	class uuid 
	{

	public:

		uuid( const unsigned long aData1, const unsigned long aData2, const unsigned long aData3, 
			const unsigned long aData4) 
			: data1( aData1),
			data2( aData2),
			data3( aData3),
			data4( aData4)
		{
			// Nothing to do
		}

		static uuid null()
		{
			return uuid(0, 0, 0, 0);
		}

		friend bool operator < (const uuid & LHS, const uuid & RHS)
		{
			if( LHS.data1 == RHS.data1) {
				if( LHS.data2 == RHS.data2) {
					if(LHS.data3 == RHS.data3) {
						return LHS.data4 < RHS.data4;
					} 
					else
						return LHS.data3 < RHS.data3;
				}
				else
					return LHS.data2 < RHS.data2;
			}

			return LHS.data1 < RHS.data1;
		}

		friend bool operator == ( const uuid & LHS, const uuid & RHS)
		{
			return ( LHS.data1 == RHS.data1) && ( LHS.data2 == RHS.data2) 
				&& ( LHS.data3 == RHS.data3) && ( LHS.data4 == RHS.data4);
		}

		friend bool operator != ( const uuid & LHS, const uuid & RHS)
		{
			return !( LHS == RHS);
		}

		friend std::ostream & operator << ( std::ostream & Stream, const uuid & Value);
		friend std::istream & operator >> ( std::istream & Stream,       uuid & Value);

		// Shouldn't private?
		unsigned long data1;
		unsigned long data2;
		unsigned long data3;
		unsigned long data4;
	};
} // End of namespace
#endif // !sfxguid_H

