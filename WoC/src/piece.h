#ifndef PIECE_H
#define PIECE_H

#include <cmath>
#include <list>
#include <map>

#define RED_SIDE true
#define BLACK_SIDE false

using Pos = std::pair<int, int>;

class Piece {   //请不要继承QObject
public:
    mutable int x, y;
    //正数
    const enum class PieceType {
        NONE = 0,
        JIANG_SHUAI = 1,
        RED_SHUAI   = 1,    BLACK_JIANG     = -1,
        SHI = 2,
        RED_SHI     = 2,    BLACK_SHI       = -2,
        XIANG = 3,
        RED_XIANG   = 3,    BLACK_XIANG     = -3,
        MA = 4,
        RED_MA      = 4,    BLACK_MA        = -4,
        JU = 5,
        RED_JU      = 5,    BLACK_JU        = -5,
        PAO = 6,
        RED_PAO     = 6,    BLACK_PAO       = -6,
        BING_ZU = 7,
        RED_BING    = 7,    BLACK_ZU        = -7
    } type;
private:
    static const std::map<PieceType, wchar_t> dict;
public:
    static inline wchar_t convert(PieceType type) {
        return dict.at(type);
    }
    inline wchar_t text() const {
        return convert(type);
    }
    inline void move(int x, int y) const {  //请勿修改
        this->x = x;
        this->y = y;
    }
    inline bool side() const {
        return type > PieceType::NONE;
    }
    inline const Pos pos() const {
        return std::make_pair(x, y);
    }
    //判断一个棋子是不是己方的
    inline bool isSidePiece(std::pair<Pos, Piece::PieceType> chess) const {
        return side()==(chess.second>Piece::PieceType::NONE);
    }
    //是否在九宫格中
    inline bool isInNinePalaces(int x,int y)const{
        return x >= 4 && x <= 6 && (y <= 3 || y >= 8);
    }
private:
    //判断走了这一步之后会不会处于被将军状态
    bool noThreat(int x, int y) const;
    virtual bool isBasicMove(int x, int y) const = 0;
public:
    //当前走法是否可行
    //即是否符合棋子基本走法并且走了这一步之后自己的王不会被将军
    virtual bool isValidMove(int x, int y) const {
        return isBasicMove(x, y) && noThreat(x, y);
    }
    //当前棋子是否可以吃掉对方的王 用于判断对方是否处于被将军状态
    //实现原理是把对方的王坐标输入isValidMove中XXXXXXXX
    //isThreat是要重写一遍给list的判断
    //和isvaildmove很类似
    virtual bool isThreat(const std::list<std::pair<Pos, Piece::PieceType>>& pieces) const = 0;
    virtual const std::list<Pos> getPossibleMoves() const = 0;

    Piece(int x, int y, PieceType type) : x(x), y(y), type(type) {}
    virtual ~Piece() {} //虚析构
};

inline Piece::PieceType removeSide(Piece::PieceType type) {
    return (Piece::PieceType)std::abs((int)type);
}

inline bool getSide(Piece::PieceType type) {
    return type > Piece::PieceType::NONE;
}

#endif // PIECE_H
