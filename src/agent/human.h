#ifndef OTHELLO_MINI_HUMAN_H
#define OTHELLO_MINI_HUMAN_H

#include "base.h"

class Human: public Agent {
public:
    Human(char _player);
    Board::Move make_move(char board[BOARD_SIZE][BOARD_SIZE]);
    void apply_reward(double reward, bool final);
};


#endif //OTHELLO_MINI_HUMAN_H
