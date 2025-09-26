

// C++ includes
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <optional>
#include <vector>

// Write a function to convert an Integer representing a number of bytes (less than or equal to 1 Gigabyte) 
// into an easy to read format, defined as follows:
//	o Maximum of 3 digits (not counting a decimal point), and a single letter to signify the unit of measure.
//	o No leading zeroes, or trailing zeroes after a decimal point.
//	o Be as accurate as possible.
//
// IMPORTANT DETAILS:
// 	 Maximum of 3 digits (not counting a decimal point), and a single letter to signify the unit of measure. Examples:
// 	o 341B = 341B
// 		o 34200B = 34.2K
// 		o 5910000B = 5.91M
// 		o 1000000000B = 1G
// 		o No leading zeroes, or trailing zeroes after a decimal point. Examples:
// 	o 34K, not 034K
// 		o 7.2M, not 7.20M
// 		o Be as accurate as possible. Example:
// 	o 54123B = 54.1K, not 54K
// 		o Note: For this problem, 1000 bytes = 1 KB, and so on.
// 		o Round to the nearest valid values
//
namespace Btl 
{
	enum class eUnit 
	{
		K,
		M,
		G
	};
	struct AmazonTest_june14
	{
		/* data */
		std::string m_str2Trim;
		size_t m_strLength;
		size_t m_strTrimLength;
		char m_unit;
	};
	
	void round2NearestVal( int aNumber2Round)
	{
		// need to check for left values and how many numbers
	}

	// Remove unwanted zero
	std::optional<AmazonTest_june14> remZero( std::string& aStr2Check)
	{
	    auto w_unitCheck = aStr2Check.length(); // number of digits
		// check for zero at the end, in the middle we do not remove them!!
        // start from the end and remove until you hit the first non=zero
		// this way it makes sense
		// reverse iterator
 		auto w_begCheck=aStr2Check.rbegin();
// 		std::reverse_iterator<int> w_endCheck=aStr2Check.rend(); 
		auto w_strCount=0;
		while( *w_begCheck++=='0')
		{
//			std::cout << "Erase a character from the string: " << *w_begCheck << "\n";
			++w_strCount; // shall get 2 for 34200
		}
		auto w_lastStr = aStr2Check.length();
		
		if( w_strCount==0) 
		  return std::nullopt;
		else  // remove zeros
		{
		   // now erase it from erase (begin+.., end)
		   auto w_dist = std::distance(aStr2Check.begin(), aStr2Check.end() - w_strCount);
		   aStr2Check.erase(aStr2Check.begin() + w_dist, aStr2Check.end());
		}

		// could replace lines above by this one
		// aStr2Check.erase( std::remove_if(aStr2Check.begin(),aStr2Check.end(), 
		// []( char aChar2Rem) {return aChar2Rem == '0';}), //logical end
		// aStr2Check.end());

		std::cout << "Erased string is: " << aStr2Check.c_str() << "\n";

		return make_optional<AmazonTest_june14>(aStr2Check,w_unitCheck,w_lastStr);        
	}

	std::string set3Digts( const std::string& aStr2Check, unsigned aOffset)
	{
		std::string w_str2Trim{aStr2Check};
		// removing zeros from fa lright to far left
		auto w_ret = remZero(w_str2Trim);

		// 
		if (w_ret.has_value())
		{
			// max number of digits==3
			// case <=3 () 
			// case >3 (strip digits and round up according to the fourth)
			if( auto w_numOfDigits = w_ret.value().m_strLength - w_ret.value().m_strTrimLength;
			    w_numOfDigits<=3)
			{
				// add code here
				switch( w_numOfDigits)
				{
				case 1:
					/* code */
					break;
				case 2:
					/* code */
					break;
				case 3:
					/* code */
					break;	
				default:
					break;
				}
				return std::string{};
			}
			else { // case>3
               std::istringstream w_iss{aStr2Check};
			   std::vector<std::string> w_vecOfStr{std::istream_iterator<std::string>{w_iss}, // begin range
			                                       std::istream_iterator<std::string>{}}; // end range
			   auto w_forthNumber = std::atoi(w_vecOfStr[3].data());
			   auto w_thirdNumber = std::atoi(w_vecOfStr[2].data());
			   if (w_forthNumber>=5) // round up
			   {
				  w_thirdNumber+=1;
			   }
			   std::string w_finalStr{aStr2Check.begin(),std::next(aStr2Check.begin(),2)};
			  // aStr2Check.erase( aStr2Check.begin()+2, aStr2Check.end());
			   w_finalStr.insert( w_finalStr.end()-1,1,*std::to_string(w_thirdNumber).c_str()); // we have our 3 digits
			   return w_finalStr;
			}
		}
		return std::string{}; // for now ok!!
	}

	// pass original string to find out the number of digits
	// 10^3, 10^6, 10^9 ('K','M','G')
	std::optional<char> getUnit( const std::string& aStr, unsigned aOffset)
	{
		std::string w_str{};
        int w_mv{};
		int w_mvtoLeft{};

		if (aStr.length()>3 && aStr.length()<6)
		{
			return std::make_optional('K');
		}
		else if (aStr.length()>6 && aStr.length()<9)
		{
			return std::make_optional('M');
			//return 'M';
		}
		else if (aStr.length()>9 && aStr.length()<12)
		{
			return std::make_optional('G');
			//return 'G';
		}
		else {return std::nullopt;}
#if 0		
		// 3 -> K
		if (w_mv + w_mvtoLeft==3)
		{
			//	std::string w_char('k');
			//w_str.insert(w_str.end(),'K');
			return 'K';
		}
		// 6 -> M
		if (w_mv+w_mvtoLeft==6)
		{
			//w_str.insert(w_str.end(),'M');
			return 'M';
		}
		// 9 -> G
		if (w_mv+w_mvtoLeft==9)
		{
			//w_str.insert(w_str.end(),'G');
			return 'G';
		}
		return char{};
#endif
	}

	// 34200 -> 34.2K
	// number of zero, move from left to right 
	// to keep 3 digits, once i have removed zero
	// check for the length of the new string.
	// if length >= 3, move dot to the left once
	// now we have moved from right to left of 3 unit,
	// which mean we have 'K'
	std::string getValueAndUnit( const std::string& aStr2Check)
	{
		if( !getUnit(aStr2Check,0).has_value())
		{
			return std::string{};
		}
		std::string w_cpyStr{aStr2Check};

        //auto w_unitChar = getUnit(aStr2Check,0);
        switch( auto w_unitChar = getUnit(aStr2Check,0); w_unitChar.value())
		{
		case 'K':
			if (w_cpyStr.length()==4)
			{
				/* code */
				auto w_str2Ret = set3Digts(aStr2Check,0);
				w_cpyStr.insert( std::next(w_cpyStr.begin()),'.');
				w_cpyStr.insert( std::next(w_cpyStr.begin(),4),'K');
				return w_cpyStr; //RVO: Return Value Optimization
			}
			else if (w_cpyStr.length()==5)
			{
				/* code */
				auto w_str2Ret = set3Digts(aStr2Check,0);
				w_cpyStr.insert( std::next(w_cpyStr.begin(),2),'.');
				w_cpyStr.insert( std::next(w_cpyStr.begin(),4),'K');
				return w_cpyStr; //RVO: Return Value Optimization
			}
			break;
		case 'M':
			/* code */
			return std::string{};
			break;
		case 'G':
			/* code */
			return std::string{};
			break;		
		default:
		    return std::string{};
			break;
		}

		return std::string{};
#if 0
		// number of digits
		int w_mvtoLeft=0;
        std::string::size_type w_mv=0;

		// remove zeroes if any 
		std::string w_str=""; //remZero(aStr2Check);
		if( w_str.empty())
		{
			// no zero removed
			w_str=aStr2Check;
		}
		// do i have more than 3 digits? maximum allowed is 3
		// if we have more than 3, we need to remove some, means 
		// move from right to left.
		if( w_str.length()>3)
		{
			// need to do something, move from right to left
			w_str.insert( w_str.end()-3,'.');
			// do we still have room to move to left
			// check number of digits before the decimal
			auto w_pos=w_str.find('.');
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
				auto mv2Left=w_str.length()-w_mvtoLeft;
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
	#endif
	}

	void setString()
	{
		auto w_offSet = 0; // debug purpose

		std::string w_str2Check{""};
		if (w_offSet == 3) // not much to do K
		{
			// no need to insert a decimal
			w_str2Check.append(1,'K');
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
        using namespace std::string_literals;

		std::string w_str2build="";
         //		
        double w_number=2.3;
		auto w_myStr=std::to_string(aNumber);
		
		// check for unit
	    set3Digts( w_myStr,0);
		
		
		w_str2build.append(w_myStr.c_str());
//		w_str2build.append(" ");
		std::cout << w_str2build << "\n";

		// check for length of string of the integer
		// original number of digits
		auto w_orgNumOfDig=w_str2build.length();
        // check for zeroes if need to be removed
		auto w_str2Check=w_str2build;
		
		//mZero(w_str2Check);
        // check original length with new length
		auto w_newLen=w_str2Check.length();
		auto w_offSet=w_orgNumOfDig-w_newLen;
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
				w_str2build.append(1,'B');
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
						w_str2Check.append(1, 'B');
						std::cout << "Number is: " << w_str2Check.c_str() << "\n";
					}
					else // ==3
					{
                       w_str2Check.append(1, '.');
					   w_str2Check.append(1, 'K');
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
			set3Digts( w_str2Check,static_cast<unsigned>(w_offSet));
		}
		// check for original length if < 3, in this case nothing to do
		// otherwise we need to investigate further and call checkUnit

		// tested with 34200, ...
		std::string w_check123 = getValueAndUnit( w_str2build);
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