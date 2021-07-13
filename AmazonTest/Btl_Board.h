
//   Author: Jean Belanger 
//   Date of creation: February 22, 2012

#ifndef btlboard_H
#define btlboard_H

// App. include
#include "Btl_Moveable.h"

namespace Btl
{
	class Board
	{
		enum eWhitePieces 
		{
           	Rook1=0,    // a,1
			Rook2=1,    // h,1
			Knight1=2,  // b,1
			Knight2=3,  // g,1
			Bishop1=4,  // c,1
            Bishop2=5,  // f,1
			Queen=4,    //
			King=5,     //
			Pawn1=6     //
		};
		typedef std::list<Moveable*>::iterator list_iter;
	public:
		enum eConfig 
		{
            initial=0,
            random=1
		};
		Board( eConfig aInitialConfig=initial);
        ~Board();
		void setPieceonBoard( Moveable* aPiecetoset) {/*not implemented yet*/}
		void moveblackPiece( Moveable::posonboard aPos);
		void movewhitePiece( eWhitePieces aPiece, Moveable::posonboard aPos);
		bool isLegalMove() const;
	private:
		eWhitePieces m_whitePiece;
		// extent of the board
		Moveable::posonboard m_min;
		Moveable::posonboard m_max;
		// position you want to move
		Moveable::posonboard m_currMove;
		std::vector<char> m_row; // horizontal board row
		// pieces on board
		std::list<Moveable*> m_blackPieces;
		std::list<Moveable*> m_whitePieces;
		void create(); // initial setting
	};

    // delete object
	struct deleteIt
	{
		template<typename T>
		void operator() (const T* aPtr2delete) const
		{
			delete aPtr2delete;
		}
	};
} // End of namespace
#endif // Include guard