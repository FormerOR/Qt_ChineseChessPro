#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "board.h"

//工具类
class Algorithms {
public:
    //判断僵局(无子可走)
    static bool isStalemate(bool side) {
        auto result = Board::getBoard()->find(-1, -1, side);

        for (const auto& [pos, type] : result) {
            auto piece = Board::getBoard()->pieces.at(pos);
            if (!piece->getPossibleMoves().empty())
                return false;
        }

        return true;
    }

    //Piece::noThreat和Algorithms::isCheck的推荐辅助函数
    //反复调用对方所有棋子的isThreat，如果都是false则没有处在被将军状态
    static inline bool isCheck(const std::list<std::pair<Pos, Piece::PieceType>>& pieces, bool side) {

    }

    static bool isCheck(bool side) {
        return isCheck(Board::getBoard()->find(), side);
    }
};

#endif // ALGORITHMS_H
