
//stl include
#include <algorithm>
// App. include
#include "Btl_Board.h"

namespace Btl 
{
	Board::Board( eConfig aInitialConfig/* =initial */)
	: m_min('a',1),
	  m_max('h',8)
	{
		m_row.reserve(8);
        m_row.push_back('a');
        m_row.push_back('b');
		m_row.push_back('c');
		m_row.push_back('d');
		m_row.push_back('e');
		m_row.push_back('f');
		m_row.push_back('g');
		m_row.push_back('h');

		// create initial config
		create();
	}

	void Board::create()
	{
		// white pieces (first row)
		m_whitePieces.push_back( new Rook  (std::make_pair('a',1) ) );
		m_whitePieces.push_back( new Knight(std::make_pair('b',1) ) );
		m_whitePieces.push_back( new Bishop(std::make_pair('c',1) ) );
		m_whitePieces.push_back( new Btl::Queen (std::make_pair('d',1) ) );
		m_whitePieces.push_back( new Btl::King  (std::make_pair('e',1) ) );
		m_whitePieces.push_back( new Bishop(std::make_pair('f',1) ) );
		m_whitePieces.push_back( new Knight(std::make_pair('g',1) ) );
		m_whitePieces.push_back( new Rook  (std::make_pair('h',1) ) );

        // pawn 
		for(int i=0; i<m_row.size();++i)
		{
			m_whitePieces.push_back( new Pawn({m_row[i],2}));
		}

		// black pieces (first row)
	    m_blackPieces.push_back( new Rook  (std::make_pair('a',8)));
		m_blackPieces.push_back( new Knight(std::make_pair('b',8)));
		m_blackPieces.push_back( new Bishop(std::make_pair('c',8)));
		m_blackPieces.push_back( new Btl::Queen(std::make_pair('d',8)));
		m_blackPieces.push_back( new Btl::King (std::make_pair('e',8)));
		m_blackPieces.push_back( new Bishop(std::make_pair('f',8)));
		m_blackPieces.push_back( new Knight(std::make_pair('g',8)));
		m_blackPieces.push_back( new Rook  (std::make_pair('h',8)));
		// pawn 
		for(int i=0; i<m_row.size();++i)
		{
			m_whitePieces.push_back(new Pawn({m_row[i],7}));
		}
	}

	Board::~Board()
	{
		// delete white pieces
		std::for_each( m_whitePieces.begin(),m_whitePieces.end(),deleteIt());
		// delete black pieces
		std::for_each( m_blackPieces.begin(),m_blackPieces.end(),deleteIt());
	}

	bool Board::isLegalMove() const
	{
		return false;
	}

	void Board::movewhitePiece( eWhitePieces aPiece, Moveable::posonboard aPos)
	{
		if( isLegalMove())
		{
			// move the piece
		}
	}
} // End of namespace