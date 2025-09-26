
#pragma once

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
	    friend class Queen;

		// position on the board
		typedef std::pair<char,int> posonboard;
		enum class eColor
		{
			black=0,
			white=1
		};
		enum class eType
		{
			rook=0,
			knight=1,
			bishop=2,
			queen=3,
			king=4, 
			pawn=5
		};

		Moveable()=default;
		virtual ~Moveable()=default;
		// the way piece moves on the board
		// to be implemented by subclass 
		virtual void move( const posonboard aPos2move)=0;
		// getter/setter
		void setPos( posonboard aPos) { m_posOnBoard=aPos;  }
		posonboard getPos() const    { return m_posOnBoard;}
		eType getType() const {return m_type;}
		void setType(eType aType2Set) {m_type=aType2Set;}
		eColor getColor() const {return m_color;}
		void setColor(eColor aColor2Set) {m_color=aColor2Set;}
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
		Queen()=default;
		Queen( posonboard aPos, eColor aColor=eColor::black) // black as default color
		: Moveable{}
		{
			setPos(aPos);
			setColor(aColor);
			setType(eType::queen);
		}
		~Queen() {}
		// queen moves any number of vacant squares in any direction 
		// along a row, column, or diagonal.
		void move( const posonboard aPos2move) override final {setPos(aPos2move);}
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
	};

	//
	// King
	//
	class King : public Moveable 
	{
	public:
		King() {}
		King( posonboard aPos, eColor aColor=eColor::black) // black as default color
		: Moveable{}
		{
			setPos(aPos);
			setColor(aColor);
			setType(eType::queen);
		}
		~King() {}
		// King moves any number of vacant squares in any direction 
		// along a row, column, or diagonal.
		void move( const posonboard aPos2move) override final {setPos(aPos2move);}
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
	};

	//
	// Rook
	//
	class Rook : public Moveable 
	{
	public:
		Rook() {}
		Rook( posonboard aPos, unsigned aID=1, eColor aColor=eColor::black) // black as default color
	    : Moveable{},
		  m_ID(aID)
		{
			m_path.resize(10);
			setPos(aPos);
			setColor(aColor);
			setType(eType::queen);
		}
		~Rook() {}
		// rook moves any number of vacant squares along rows or columns 
		// (forward, backward, left or right)
		void move( const posonboard aPos2move) override final
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

	class Bishop : public Moveable 
	{
		public:

		Bishop( posonboard aPos, eColor aColor=eColor::black) // black as default color
	    : Moveable{}
		{
		//	m_path.resize(10);
			setPos(aPos);
			setColor(aColor);
			setType(eType::queen);
		}
 
		void move( const posonboard aPos2move) override final {} 
	};
	class Knight : public Moveable 
	{ 
	    public:

		Knight( posonboard aPos, eColor aColor=eColor::black) // black as default color
	    : Moveable{}
		{
		//	m_path.resize(10);
			setPos(aPos);
			setColor(aColor);
			setType(eType::queen);
		}
		void move( const posonboard aPos2move) override final {} 
	}; 
	class Pawn   : public Moveable 
	{
	public:
		Pawn() {}
		Pawn( posonboard aPos, unsigned aID=1, eColor aColor=eColor::black) // black as default color
		: Moveable{},
		  m_ID(aID)
		{
			setPos(aPos);
			setColor(aColor);
			setType(eType::queen);
		}
		//~Pawn() {/*nothing to do*/}
		
		void move( const posonboard aPos2move) override final
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