#ifndef KING_H
#define KING_H

#include "piece.h"
#include "board.h"

class King:public Piece{
public :
    King(int x,int y,bool side):Piece(x,y,side ? PieceType::RED_SHUAI : PieceType::BLACK_JIANG){}
    virtual bool isBasicMove(int x, int y) const{
        //if(!Board::getBoard()->find(x,y,side()).empty())return false;
        static const Pos s[4] = { {0,1},{0,-1},{1,0},{-1,0} };//将帅可以到达的四个点位
        if(Board::getBoard()->find(x,y).empty() || !isSidePiece(*(Board::getBoard()->find(x,y).begin())))//要去的位置是否为空或者是敌方的一个棋子
        {
            if(isInNinePalaces(x,y))//要去的地方是否是在九宫格里
            {
                for(int i=0;i<4;i++)
                {
                    if ((x==this->x+s[i].first)&&(y==this->y+s[i].second))//是否满足将帅只走左右上下的规则
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }
};
#endif // KING_H
