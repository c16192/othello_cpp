#ifndef PROJECT_BOARD_H
#define PROJECT_BOARD_H

#include "const.h"

class Board {
public:
    class Move {
    public:
        int h;
        int w;
        Move(int _h, int _w);
    };

    class Score {
    public:
        int black;
        int white;
        Score(int _b, int _w);
    };

    Board();
    Board(Board &b);
    bool make_move(Move move);
    bool is_legal_move(Move move);
    bool exist_moves(void);
    char opponent(void);
    void switch_players(void);
    char get_player(void);
    void print(void);
    void get_board_state(char (&b)[BOARD_SIZE][BOARD_SIZE]);
    Score get_result(void);

private:
    char board[BOARD_SIZE][BOARD_SIZE];
    bool is_front[BOARD_SIZE][BOARD_SIZE];
    void update_front(int h, int w);
    bool on_board(int h, int w);
    bool iterate(int &h, int &w, Direction dir, bool over_empty);
    char currentPlayer;
};


#endif //PROJECT_BOARD_H
