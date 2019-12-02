#ifndef PROJECT_BOARD_H
#define PROJECT_BOARD_H

#include "const.h"

class Board {
private:
    char board[BOARD_SIZE][BOARD_SIZE];
    bool is_front[BOARD_SIZE][BOARD_SIZE];
    void update_front(int h, int w);
    bool iterate(int &h, int &w, Direction dir, bool over_empty);
    char currentPlayer;

public:
    Board();
    bool make_move(int h, int w);
    bool on_board(int h, int w);
    bool is_legal_move(int h, int w);
    bool exist_moves(void);
    char opponent(void);
    void switch_players(void);
    char get_player(void);
    void print(void);
};


#endif //PROJECT_BOARD_H
