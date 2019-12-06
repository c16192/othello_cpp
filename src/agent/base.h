#ifndef OTHELLO_MINI_BASE_H
#define OTHELLO_MINI_BASE_H

#include "../const.h"
#include "../board.h"

class Agent {
protected:
    char player;
public:
    virtual Board::Move make_move(char board[BOARD_SIZE][BOARD_SIZE]) = 0;
    virtual void apply_reward(double reward, bool final) = 0;
};


#endif //OTHELLO_MINI_BASE_H
