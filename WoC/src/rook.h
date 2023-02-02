#ifndef ROOK_H
#define ROOK_H

#include "piece.h"
#include "board.h"

class Rook : public Piece
{
private:

public:
    Rook(int x,int y,bool side):Piece(x,y,side ? PieceType::RED_JU: PieceType::BLACK_JU){};
    virtual bool isBasicMove(int x,int y)const{

    }
    virtual const std::list<Pos> getPossibleMoves() const{

    }
    virtual bool isThreat(const std::list<std::pair<Pos, Piece::PieceType>>& pieces)const{

    }
};

#endif // ROOK_H
