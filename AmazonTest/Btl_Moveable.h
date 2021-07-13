
//  Author: Jean Belanger 
//  Date of creation: February 22, 2012 

#ifndef btlmoveable_H
#define btlmoveable_H

// stl includes
#include <vector>
#include <deque>

namespace Btl
{
// 	Each piece moves in a different way.
// 		The rook moves any number of vacant squares along rows or columns (forward, backward, left or right). 
//  	It also is involved (with the king) in the special move called castling.
//
// 		The bishop moves any number of vacant squares diagonally. Consequently a bishop stays on squares of 
//      the same color throughout a game. The two bishops each player starts with move on squares of opposite colors.
// 		
//      The queen moves any number of vacant squares in any direction along a row, column, or diagonal.
// 		
//      The king moves only one vacant square in any direction. It can also castle in conjunction with a rook.
// 		
//      The knight moves to a vacant square in an "L"-shape (two spaces forward, backward, left, or right, 
//      then one space perpendicular). The knight jumps over any intervening piece(s) when moving.
// 		
//       The pawn can only move forward one space, or optionally two spaces when on its starting square, 
//      in a straight line away from the player
// 
	// abstract class
	class Moveable 
	{
	public:
		// position on the board
		typedef std::pair<char,int> posonboard;
		enum eColor
		{
			black=0,
			white=1
		};
		enum eType
		{
			rook=0,
			knight=1,
			bishop=2,
			queen=3,
			king=4, 
			pawn=5
		};
		Moveable() {}
		virtual ~Moveable() {}
		// the way piece moves on the board
		// to be implemented by subclass 
		virtual void move( const posonboard aPos2move)=0;
		// getter/setter
		void setPos( posonboard aPos) { m_posOnBoard=aPos;  }
		posonboard getPos() const    { return m_posOnBoard;}
		eType getType() const {return m_type;}
		eColor getColor() const {return m_color;}
		const std::deque<posonboard>& getPath() const {return m_path;}
	protected:
		eType m_type;
		eColor m_color;
		// position on the chess board
		posonboard m_posOnBoard;
		// container of position along the path
		std::deque<posonboard> m_path;
	};
	
	//
	// Queen
	//
	class Queen : public Moveable 
	{
	public:
		Queen() {}
		Queen( posonboard aPos, eColor aColor=black) // black as default color
		: m_posOnBoard(aPos),
		  m_color(aColor),
		  m_type(Moveable::queen)
		{
			// nothing to do
		}
		~Queen() {}
		// queen moves any number of vacant squares in any direction 
		// along a row, column, or diagonal.
		void move( const posonboard aPos2move) {setPos(aPos2move);}
		bool operator== (const Queen& aOther) 
		{
			return ( m_posOnBoard.first==aOther.m_posOnBoard.first &&
				m_posOnBoard.second==aOther.m_posOnBoard.second);
		}
		const bool operator== (const Queen& aOther) const
		{
			return ( m_posOnBoard.first==aOther.m_posOnBoard.first &&
				m_posOnBoard.second==aOther.m_posOnBoard.second);
		}
	private:
		// current position on the board
		//std::pair<char,int> m_posOnBoard;
	};

	//
	// King
	//
	class King : public Moveable 
	{
	public:
		King() {}
		King( posonboard aPos, eColor aColor=black) // black as default color
		: m_posOnBoard(aPos),
		  m_color(aColor),
		  m_type(Moveable::king)
		{
			// nothing to do
		}
		~King() {}
		// King moves any number of vacant squares in any direction 
		// along a row, column, or diagonal.
		void move( const posonboard aPos2move) {setPos(aPos2move);}
		bool operator== (const King& aOther) 
		{
			return ( m_posOnBoard.first==aOther.m_posOnBoard.first &&
				m_posOnBoard.second==aOther.m_posOnBoard.second);
		}
		const bool operator== (const King& aOther) const
		{
			return ( m_posOnBoard.first==aOther.m_posOnBoard.first &&
				m_posOnBoard.second==aOther.m_posOnBoard.second);
		}
	private:
	};

	//
	// Rook
	//
	class Rook : public Moveable 
	{
	public:
		Rook() {}
		Rook( posonboard aPos, unsigned aID=1, eColor aColor=black) // black as default color
	    : m_posOnBoard(aPos),
		  m_ID(aID),
	      m_color(aColor),
		  m_type(Moveable::rook)
		{
			m_path.resize(10);
		}
		~Rook() {}
		// rook moves any number of vacant squares along rows or columns 
		// (forward, backward, left or right)
		void move( const posonboard aPos2move) 
		{
			// current position
			m_path.push_front(m_posOnBoard);
			char w_col=aPos2move.first;
			// check for left or right of current
			// how many steps to do
			// push in the container
			// check up or down
			// how many steps to do
			// push in the container
		}
		
		// ...
		unsigned getID() const {return m_ID;}
		void setID(unsigned aID) {m_ID=aID;}
        // check for equality
		bool operator== (const Rook& aOther) 
		{
			return ( m_posOnBoard.first==aOther.m_posOnBoard.first &&
				m_posOnBoard.second==aOther.m_posOnBoard.second);
		}
	private:
		unsigned m_ID; // 1,2
		// container of position along the path
		std::deque<posonboard> m_path;
	};
	class Bishop : public Moveable {};
	class Knight : public Moveable {}; 
	class Pawn   : public Moveable 
	{
	public:
		Pawn() {}
		Pawn( posonboard aPos, unsigned aID=1, eColor aColor=black) // black as default color
		: m_posOnBoard(aPos),
		  m_ID(aID),
		  m_color(aColor),
		  m_type(Moveable::pawn)
		{
			// nothing to do
		}
		~Pawn() {/*nothing to do*/}
		//
		void move( const posonboard aPos2move) 
		{
			// forward one space
		}
		// ...
		unsigned getID() const {return m_ID;}
		void setID(unsigned aID) {m_ID=aID;}
		// check for equality
		bool operator== (const Pawn& aOther) 
		{
			return ( m_posOnBoard.first==aOther.m_posOnBoard.first &&
				m_posOnBoard.second==aOther.m_posOnBoard.second);
		}
	private:
		unsigned m_ID; // 1,2,3,4,5,6,7,8
	};
} // End of namespace
#endif // Include guard