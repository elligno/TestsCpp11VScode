
#pragma once

#include <iostream>
#include <vector>>

namespace Btl 
{
    // 
	// ...
    class Grid
    {
		struct Hit{};
    public:
		typedef std::vector<std::vector<char> > vecofvec;
        Grid()
		{
			m_grid.reserve(3); // row allocation
			for(int i=0; i<m_grid.capacity(); ++i)
				m_grid[i].reserve(3);
		}
        void registerAlgo( TicTacToeAlgorithm* aAlgo)
		{
			m_Algo=aAlgo;
		}
		void notify() { m_Algo->checkTicTacToe();}
		void setHit( unsigned aI,unsigned aJ, char aHit)
		{
			m_grid[aI][aJ]=aHit;
			notify(); // check for tic-tac-toe
		}
		const vecofvec& getArr2D() const {return m_grid;}
    protected:
    private:
        TicTacToeAlgorithm* m_Algo;
// 		struct cell
// 		{	
// 			cell(): w_XO('') {} // empty
// 			std::pair<int,int> gridIndex;
// 			char w_XO;
// 		};
		// vector of row, each has 3 columns
		vecofvec m_grid;
    };

	// ...
	class TicTacToeAlgorithm 
	{
	public:
		TicTacToeAlgorithm( Grid* aGird) : m_grid(aGird) {}
		// tic-tac-toe algorithm
		bool checkTicTacToe()
		{
			typedef std::vector<std::vector<char> > vecofvecChar;
			typedef std::iterator_traits<std::vector<char>::iterator>::difference_type diff_type;
			
			// loop on row and column and check 
			// for char alignment 
			const Grid::vecofvec& theChars=m_grid->getArr2D();
			
			// row iterator
			auto firstRow = theChars.begin();
			auto lastRow = theChars.end();
			std::vector<char> w_rowChar(3);
			int i(0);
			while(firstRow!=lastRow)
			{
				// beginning of the row
                auto begRow=(*firstRow).begin();
				auto endRow=(*firstRow).end();
				while (begRow!=endRow)
				{
					w_rowChar[i++]=*begRow++;
				}
				diff_type w_diffX=std::count( w_rowChar.begin(),w_rowChar.end(),'x');
				diff_type w_diffO=std::count( w_rowChar.begin(),w_rowChar.end(),'o');
				if ((w_diffX==3) || (w_diffO==3))
				{
					std::cout << "We have tic-tac-toe\n";
					break;
				}
				++firstRow; // next row
				i=0; // reset vector index
			}
		
			// column iterator
			typedef std::vector<char>::const_iterator const_char_iter;
			std::vector<const_char_iter> w_vecolIter(3);
			// initialization 
			auto firstR=theChars.begin();
			for (std::vector<const_char_iter>::size_type l=0; w_vecolIter.size();++l)
			{
				// set first column element 
				w_vecolIter[l] = firstR->begin();
				++firstR;
			}

			// sock column elements
			std::vector<char> w_colElements(3);
			// loop on column
			for(std::vector<const_char_iter>::size_type i=0; i<3;++i)
			{
				for (std::vector<char>::size_type k=0;k<w_colElements.size();++k)
				{
					w_colElements[k]=*w_vecolIter[k];
					++w_vecolIter[k];
				}

				// check for the tic-tac-toe
				diff_type w_diffX=std::count( w_colElements.begin(),w_colElements.end(),'x');
				diff_type w_diffO=std::count( w_colElements.begin(),w_colElements.end(),'o');
				if ((w_diffX==3) || (w_diffO==3))
				{
					std::cout << "We have tic-tac-toe\n";
					break;
				}
				++firstRow; // next row
				i=0; // reset vector index
			}
		}
	private:
// 		unsigned charXCounter;
// 		unsigned charOCounter;
		Grid* m_grid;
	};
 } // End of namespace