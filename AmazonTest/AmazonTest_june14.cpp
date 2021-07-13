
// Author: Jean Belanger (Elligno Inc.)
// Date of creation: June 08, 2014

// C++ includes
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
// test include
#include "Btl_StringUtil.h"


// Write a function to convert an Integer representing a number of bytes (less than or equal to 1 Gigabyte) 
// into an easy to read format, defined as follows:
//	� Maximum of 3 digits (not counting a decimal point), and a single letter to signify the unit of measure.
//	� No leading zeroes, or trailing zeroes after a decimal point.
//	� Be as accurate as possible.
//
// IMPORTANT DETAILS:
// 	 Maximum of 3 digits (not counting a decimal point), and a single letter to signify the unit of measure. Examples:
// 	o 341B = 341B
// 		o 34200B = 34.2K
// 		o 5910000B = 5.91M
// 		o 1000000000B = 1G
// 		� No leading zeroes, or trailing zeroes after a decimal point. Examples:
// 	o 34K, not 034K
// 		o 7.2M, not 7.20M
// 		� Be as accurate as possible. Example:
// 	o 54123B = 54.1K, not 54K
// 		� Note: For this problem, 1000 bytes = 1 KB, and so on.
// 		� Round to the nearest valid values

namespace Btl 
{
	void round2NearestVal( int aNumber2Round)
	{
		// need to check for left values and how many numbers
	}

	// Remove unwanted zero
	void remZero( std::string& aStr2Check)
	{
		// check for zero at the end, in the middle we do not remove them!!
        // start from the end and remove until you hit the first non=zero
		// this way it makes sense
		// reverse iterator
 		std::string::reverse_iterator w_begCheck=aStr2Check.rbegin();
// 		std::reverse_iterator<int> w_endCheck=aStr2Check.rend(); 
		unsigned w_strCount=0;
		while (*w_begCheck++=='0')
		{
//			std::cout << "Erase a character from the string: " << *w_begCheck << "\n";
			++w_strCount; // shall get 2 for 34200
			// erase and count
			//aStr2Check.erase(w_begCheck);
			//std::cout << "New string after erasing a character: " << aStr2Check.c_str() << "\n";
		}
		// now erase it from erase (begin+.., end)
		std::string::difference_type w_dist=
			std::distance(aStr2Check.begin(),aStr2Check.end()-w_strCount);
        aStr2Check.erase(aStr2Check.begin()+w_dist,aStr2Check.end());
		std::cout << "Erased string is: " << aStr2Check.c_str() << "\n";

		// check for zero, then remove it
// 		std::string::const_iterator w_beg=aStr2Check.begin();
// 		std::string::const_iterator w_end=aStr2Check.end();
// 		std::string::size_type w_len=aStr2Check.length();
		
		// not much to do except if there is zero
		// check if integer contains zero, how i do that?
		// check char by char
// 		int w_zeroCounter=0;
// 		std::string w_str2Ret;
// 		while (w_beg!=w_end)
// 		{
// 			if(*w_beg=='0')
// 			{
// 				++w_zeroCounter;
// 			}
// 			++w_beg;
// 		} // while-loop
// 		if ( w_zeroCounter!=0)
// 		{
// 			// need to remove the zero
// 			int w_newLen=w_len-w_zeroCounter;
// 			std::copy(aStr2Check.begin(),aStr2Check.begin()+w_newLen,
// 				std::back_inserter(w_str2Ret));
// 		}
		// return string without zero
	//	return w_str2Ret;
	}

	void setUnit( std::string& aStr2Check, unsigned aOffset)
	{
		// we know length greater than 3, we have at least 4 digits
		// we can set at least K unit (move decimal to the left by 3)
        // let's move 3 digits to the left, we still have room 
		std::string w_afterDec;
		// allowed to keep 3 digits excluding decimal
		std::copy(aStr2Check.begin()+2, aStr2Check.end(),
			std::back_inserter(w_afterDec));
		// check for size of the new string
		std::string::size_type w_after=w_afterDec.size();
		// let's suppose that we have 2 digits
		// need to check the last one > 5, then increment the first by 1
		// otherwise don't touch it
		std::string::const_iterator w_num=w_afterDec.begin();
		const char* w_char=&*w_num;
		int w_myNum=::atoi(&*w_num);
		std::cout << "Number representation is: " << w_myNum << "\n";
	}

	// ...
	std::string getUnit( const std::string aStr, unsigned aOffset)
	{
		std::string w_str;

		// 3 -> K
		if (w_mv+w_mvtoLeft==3)
		{
			//	std::string w_char('k');
			w_str.insert(w_str.end(),'K');
			//return 'K';
		}
		// 6 -> M
		if (w_mv+w_mvtoLeft==6)
		{
			w_str.insert(w_str.end(),'M');
			//return 'M';
		}
		// 9 -> G
		if (w_mv+w_mvtoLeft==9)
		{
			w_str.insert(w_str.end(),'G');
			//return 'G';
		}
		return w_str;
	}
	// 34200 -> 34.2K
	// number of zero, move from left to right 
	// to keep 3 digits, once i have removed zero
	// check for the length of the new string.
	// if length >= 3, move dot to the left once
	// now we have moved from right to left of 3 unit,
	// which mean we have 'K'
	std::string check4Unit( std::string& aStr2Check)
	{
		// number of digits
		int w_mvtoLeft=0;
        std::string::size_type w_mv=0;

		// remove zeroes if any 
		std::string w_str=""; //remZero(aStr2Check);
		if (w_str.empty())
		{
			// no zero removed
			w_str=aStr2Check;
		}
		// do i have more than 3 digits? maximum allowed is 3
		// if we have more than 3, we need to remove some, means 
		// move from right to left.
		if (w_str.length()>3)
		{
			// need to do something, move from right to left
			w_str.insert( w_str.end()-3,'.');
			// do we still have room to move to left
			// check number of digits before the decimal
			std::string::size_type w_pos=w_str.find('.');
			std::cout << w_pos << "\n";
			if(w_pos>3)
			{
				// we have room to move
				w_str.erase( w_str.begin()+w_pos+2,w_str.end());
				std::cout << "move again\n";
			}
			else
			{
				// round number, remove at the end
				w_str.erase( w_str.begin()+w_pos+2,w_str.end());
				w_mv=3;
			}
		}
		else // less or equal to 3, ok it is allowed
		{
			// need to check unit
			// ==3, ==2, ==1
			w_mv=aStr2Check.length()-w_str.length();
			if (w_mv!=0) // we have removed zero (342)
			{
				// we have to move from right to left of w_mv
				if (w_mv<3) // we have room to move
				{
					do
					{
                       w_mvtoLeft+=1; // move to the left
					} while(w_mv+w_mvtoLeft!=3);
				}	
				// check for unit
				int mv2Left=w_str.length()-w_mvtoLeft;
				w_str.insert(w_str.begin()+mv2Left,'.');
			}
			else
			{
			    w_str.insert(w_str.end(),'B');
			}
		}

		// 3 -> K
		if (w_mv+w_mvtoLeft==3)
		{
		//	std::string w_char('k');
			w_str.insert(w_str.end(),'K');
			//return 'K';
		}
		// 6 -> M
		if (w_mv+w_mvtoLeft==6)
		{
			w_str.insert(w_str.end(),'M');
			//return 'M';
		}
		// 9 -> G
		if (w_mv+w_mvtoLeft==9)
		{
			w_str.insert(w_str.end(),'G');
			//return 'G';
		}
		return w_str;
	}

	void setString()
	{
		if (w_offSet == 3) // not much to do K
		{
			// no need to insert a decimal
			w_str2Check.append('K');
		}
		else if (w_offSet == 2) // can move to left by 1
		{
			// insert a decimal
		}
		else if (w_offSet == 1) // can move to left by 2
		{
		}
	}
	// main entry point
	void convert2EasyRead(int aNumber)
	{
		// check number of digits (length), allowed max. of 3 digits
		
		// algorithm
		// convert integer into a string, so i can check the length of integer
		// if already 3 digits (check for zero if any)
		// check for zero at the end if there is any, if yes remove it
		// then check again the length
		// 

		std::string w_str2build="";
//		double w_number=2.3;
		std::string w_myStr=Btl::ToString(aNumber);
		w_str2build.append(w_myStr.c_str());
//		w_str2build.append(" ");
		std::cout << w_str2build << "\n";

		// check for length of string of the integer
		// original number of digits
		std::string::size_type w_orgNumOfDig=w_str2build.length();
        // check for zeroes if need to be removed
		std::string w_str2Check=w_str2build;
		remZero(w_str2Check);
        // check original length with new length
		std::string::size_type w_newLen=w_str2Check.length();
		std::string::size_type w_offSet=w_orgNumOfDig-w_newLen;
		unsigned w_numOfDigits=0;
//		if (w_offSet!=0) // zeroes removed
//		{
// 			if (w_offSet == 3) // not much to do K
// 			{
// 				// no need to insert a decimal
// 				w_str2Check.append('K');
// 			}
// 			else if (w_offSet == 2) // can move to left by 1
// 			{
// 				// insert a decimal
// 			}
// 			else if (w_offSet == 1) // can move to left by 2
// 			{
// 			}
//		}
//		else // no zeroes in the string
//		{
//			w_numOfDigits=w_orgNumOfDig;
//		}
		
		if (w_numOfDigits<=3) // maximum digits allowed
		{
			// check for offset==0 or not
			if (w_offSet==0)
			{
				// no unity
				w_str2build.append('B');
				std::cout << "Number is: " << w_str2build.c_str() << "\n";
			}
			else // offset !=0
			{
				switch (w_numOfDigits)
				{
				case 1: // only 1 digits
					// check offset, cannot move to the left
					// offset == 0 return string as it is
					// else check unity
					if (w_offSet<3)
					{
						w_str2Check.append('B');
						std::cout << "Number is: " << w_str2Check.c_str() << "\n";
					}
					else // ==3
					{
                       w_str2Check.append('.');
					   w_str2Check.append('K');
					   std::cout << "Number is: " << w_str2build.c_str() << "\n";
					}
					break;
				case 2: // only 2 digits
					// check offset, can only move by 1 to the left
					if (w_offSet==1)
					{
						// return as it is
					}
					else
					{
						// do-while
					}
					break;
				case 3: // only 3 digits
					break;
				}
			}
		}
		else // >3 over maximu allowed
		{
			// check for unit
			setUnit( w_str2Check,w_offSet);
		}
		// check for original length if < 3, in this case nothing to do
		// otherwise we need to investigate further and call checkUnit

		// tested with 34200, ...
		std::string w_check123=check4Unit( w_str2build);
		std::cout << "The following string in a easy to read format is: " << w_check123.c_str() << "\n";

		// check for zero in the number
	//	std::string w_str=remZero(w_str2build);
		// check for length with original
	//	if ( w_str.length()!=w_len) // if different, 1200 => 1.2K 
	//	{
			// zero removed
//			char w_unit = check4Unit(w_str);
			// need to add a point and the unit
			// insert the point or decimal
			// need to append unit at the end
	//	}
	}
} // End of namespace
