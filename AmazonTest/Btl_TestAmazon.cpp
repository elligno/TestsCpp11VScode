
//  Author: Jean Belanger
//  Date of creation: February 22, 2012
//  Revision history:

// C++ includes
#include <cmath>
#include <iostream>
// stl includes
#include <algorithm>
#include <vector>
#include <set>
#include <numeric>  // accumulate
// App. includes
#include "Btl_Sqrt.hpp"

// Coding Sample Request:

// 1)	Implement a deque from scratch.  It should be able to grow dynamically.  
//      Try to make it as efficient as possible (minimizing resizings).
//      (#include "Btl_myDeque.hpp)"

// 2)	Given a char pointer to a large buffer of memory, 
//      write your own version of malloc and free without using system calls.  
//      Try to make it as efficient and robust as possible, and minimize fragmentation.
//      (just don't know how to do it)

// 3)	Implement an algorithm that plays tic-tac-toe.
//      (#include Btl_TicTacToeAlgorithm.h)

// 4)	A ladder has n-steps.  You can take 1 or 2 rungs at a time.  
//      Write a function that will print out all of the possible combinations (eg, 122121, 1121121, etc)
//      (see function "printCombinations" below)

// 5)	Write an algorithm to calculate the square root of a number.
//      (#include "Btl_sqrt.hpp")

// 6)	The function boolean numExists(int[] array, int num), 
//      takes a sorted array and an integer, and returns true if 
//      the number is found in the array.  Implement this function as efficiently as possible.
//      (see function "numExists" below)

// 7)	Write atoi. 
//      (#include "Btl_Atoi.h")

// 8)	Write a chess framework with classes for each piece as well as for the board.  
//      Have a method that randomly places some pieces on the board, both black and white.  
//     Write a method that computes all of the legal moves for either player.
//     (#include "Btl_Moveable.h, Btl_Board.h", Btl_Board.cpp)

namespace Btl 
{
	//  Question #6 
	//     The function boolean numExists(int[] array, int num), 
	//     takes a sorted array and an integer, and returns true if 
	//     the number is found in the array.  Implement this function as efficiently as possible.
	//
	bool numExists( int array[], int num) 
	{
		// array size
		const int N = sizeof(array)/sizeof(int);
		// initialize the set
		std::set<int> w_setofInt(array,array+N);
		std::set<int>::iterator valueIt=w_setofInt.find(num);
		if (valueIt!=w_setofInt.end())
		{
			// we found the number
			std::cout << "The number that we have found is:" << *valueIt << std::endl; 
			return true;
		}
		return false;
	}

	// Question #5	
	//    Write an algorithm to calculate the square root of a number.
	// 
    double computeSquareroot()
	{
		// call our sqrt class
		std::cout << "Sqrt<16>::result = " << Btl::Sqrt<16>::result << "\n";
		std::cout << "Sqrt<25>::result = " << Btl::Sqrt<25>::result << "\n";
		std::cout << "Sqrt<42>::result = " << Btl::Sqrt<42>::result << "\n";
		std::cout << "Sqrt<1>::result  = " << Btl::Sqrt<1>::result << "\n";

		return 0.;
	}

	// Question #4	
	//   A ladder has n-steps.  You can take 1 or 2 rungs at a time.  
	//   Write a function that will print out all of the possible combinations (eg, 122121, 1121121, etc)
	//
	// [1,1,1,1,2,2,2,1,1,2]
	// range change dynamically
	// std::rotate algorithm
	// algorithm std::generate_n
	// case 1 step=1 combination
	// case 2 steps=1 combination
	// case 3 steps=
	// print combination
	// std::copy(ostream_iterator<int>)
	//
	void printCombinations( int aNsteps)
	{
		// fix a range of sequence
        [[maybe_unused]] int w_intNumsteps{};
		int minSeq{};
		int maxSeq{};
		std::vector<int> w_try2Find;
		w_try2Find.reserve(aNsteps);
		// start with 3 (1 and 2 are trivial case)
        w_try2Find.push_back(2);
		w_try2Find.push_back(2);
		w_try2Find.push_back(2);
        for (int bb=1; bb<w_try2Find.size();++bb)
        {
			if (std::accumulate(w_try2Find.begin(),w_try2Find.end(),0)<aNsteps)
			{
				w_try2Find.push_back(2);
			}
			break;
			minSeq=bb;
			maxSeq=aNsteps;
        }

		// create a vector of sequence
		std::vector<int> w_seq(aNsteps);
		// initialize sequence (all set to 1)
		std::fill( w_seq.begin(),w_seq.end(),1);
		// check if the sum is equal to the number of steps
		if (std::accumulate(w_seq.begin(),w_seq.end(),0)==aNsteps)
		{
			// then print the sequence
			std::copy(w_seq.begin(),w_seq.end(),
				std::ostream_iterator<int>(std::cout," "));
			std::cout << std::endl;
		}

		// generate new sequences
		std::vector<int> w_newSeq(w_seq.begin(),w_seq.end());
		std::vector<int>::iterator beg=w_newSeq.begin();
		std::vector<int>::const_iterator end=w_newSeq.end();
		int jj=1;
		while (beg!=end)
		{
			// change the last element of the sequence (=2)
			w_newSeq[w_newSeq.size()-jj++]=2;
			// check if the sum is equal to the number of steps
			if (std::accumulate(w_newSeq.begin(),w_newSeq.end(),0)==aNsteps)
			{
				// then print the sequence
				std::copy(w_newSeq.begin(),w_newSeq.end(),
					std::ostream_iterator<int>(std::cout," "));
				std::cout << std::endl;
				// rotate the elements in the range (other combination)
				for (int ii=1;ii<w_newSeq.size()-1;++ii)
				{
					// mid
					std::vector<int>::iterator mid=w_newSeq.begin()+ii;
					std::rotate(w_newSeq.begin(),mid,w_newSeq.end());
					// then print the sequence
					std::copy(w_newSeq.begin(),w_newSeq.end(),
						std::ostream_iterator<int>(std::cout," "));
					std::cout << std::endl;
				}
			}
		} // while
	}

	// Question #3
	//   Implement an algorithm that plays tic-tac-toe.
	//
	void TicTacToeAlgorithm()
	{
	}
} // End of namespace
