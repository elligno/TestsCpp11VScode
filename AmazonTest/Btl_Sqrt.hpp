
//  Author: Jean Belanger 
//  Date of creation: February 22, 2012
//  

#ifndef btlsqrt_H
#define btlsqrt_H

namespace Btl 
{
	// make use of metaprogram to compute the square root
	// Description:
	//  The recursion proceeds using a binary search technique 
	//  (often called method of bisection). Inside the template,
	//  we compute if the result is in the first or second half 
	//  of the range between LO and HI. This case differentiation 
	//  is done using the conditional operator ?:. if mid^2 is 
	//  greater than N, we continue to search in the first half.
	//  if mid^2 is less or equal to N, we use the same template
	//  for the second half again.
	//
	//  The specialization that ends the recursive process is
	//  when LO and HI have the same value M, which is the final result.
    //
	// primary template to compute sqrt(N)
	template<int N, int LO=1, int HI=N>
	class Sqrt 
	{
	public:
		// compute the midpoint, rounded up
		enum {mid=(LO+HI+1)/2};

		// search a not too large value in the halved interval
		enum {result = (N<mid*mid) ? Sqrt<N,LO,mid-1>::result
			                       : Sqrt<N,mid,HI>::result};
	};

	//
	// partial specialization for the case when LO equal HI
	//
	template<int N, int M>
	class Sqrt<N,M,M>
	{
	public:
		enum {result=M};
	};
} // End of namespace
#endif // Include guard