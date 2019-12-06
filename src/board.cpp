#include "board.h"
#include "utils.h"
#include <iostream>
using namespace std;

Board::Board() {
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = EMPTY;
            is_front[i][j] = false;
        }
    }

    board[3][4] = BLACK;
    board[4][3] = BLACK;
    board[3][3] = WHITE;
    board[4][4] = WHITE;
    for(int i = 0; i < 3; i++) {
        is_front[i+2][2] = true;
        is_front[2][i+3] = true;
        is_front[5][i+2] = true;
        is_front[i+3][5] = true;
    }

    currentPlayer = BLACK;
}

Board::Board(Board &b) {
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            this->board[i][j] = b.board[i][j];
            this->is_front[i][j] = b.is_front[i][j];
        }
    }
    this->currentPlayer = b.currentPlayer;
}

bool Board::on_board(int h, int w) {
    return (h >= 0) && (h < BOARD_SIZE) && (w >= 0) && (w < BOARD_SIZE);
}

void Board::print(void) {
    print_board(board);
}

/* Iterates over a row, column, or diagonal in a given direction
 * Returns false if it goes out of the board
 * Else, returns true if board is empty and over_empty is set to true,
 * or if the board is full and over_empty is set to false
 * Returns false otherwise.
 */
bool Board::iterate(int &h, int &w, Direction dir, bool over_empty) {
    if(dir == U || dir == UR || dir == UL) {
        h--;
    } else if(dir == D || dir == DR || dir == DL) {
        h++;
    }
    if(dir == UL || dir == L || dir == DL) {
        w--;
    } else if(dir == UR || dir == R || dir == DR) {
        w++;
    }
    return Board::on_board(h, w) && ((board[h][w] == EMPTY) == over_empty);
}

char Board::opponent() {
    return currentPlayer == BLACK ? WHITE : BLACK;
}

bool Board::is_legal_move(Move move) {
    int h = move.h;
    int w = move.w;
    if(!Board::on_board(h, w) || !is_front[h][w]) return false;
    for(int dir = 0; dir < NUM_DIR; dir++) {
        int _h = h;
        int _w = w;
        if(!Board::iterate(_h, _w, (Direction) dir, false) || board[_h][_w] == currentPlayer) continue;
        while(Board::iterate(_h, _w, (Direction) dir, false)){
            if(board[_h][_w] == currentPlayer) return true;
        }
    }
    return false;
}

bool Board::make_move(Move move) {
    int h = move.h;
    int w = move.w;
    if(!Board::on_board(h, w) || !is_front[h][w]) return false;
    bool is_legal_move = false;
    for(int dir = 0; dir < NUM_DIR; dir++) {
        int _h = h;
        int _w = w;
        if(!Board::iterate(_h, _w, (Direction) dir, false) || board[_h][_w] == currentPlayer) continue;
        bool turn_over = false;
        while(Board::iterate(_h, _w, (Direction) dir, false)){
            if(board[_h][_w] == currentPlayer) {
                turn_over = true;
                is_legal_move = true;
                break;
            }
        }
        if(turn_over) {
            _h = h, _w = w;
            while(Board::iterate(_h, _w, (Direction) dir, false)){
                if(board[_h][_w] == currentPlayer) {
                    break;
                }
                board[_h][_w] = currentPlayer;
            }
        }
    }
    if(is_legal_move) {
        board[h][w] = currentPlayer;
        currentPlayer = Board::opponent();
        Board::update_front(h, w);
    }
    return is_legal_move;
}

void Board::update_front(int h, int w) {
    if(!Board::on_board(h, w) || !is_front[h][w]) {
        cout << "Frontier update failed";
        throw -1;
    }
    is_front[h][w] = false;
    for(int dir = 0; dir < NUM_DIR; dir++) {
        int _h = h;
        int _w = w;
        if(Board::iterate(_h, _w, (Direction) dir, true)) is_front[_h][_w] = true;
    }
}

bool Board::exist_moves() {
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            if(!is_front[i][j]) continue;
            if(is_legal_move(Move(i, j))) return true;
        }
    }
    return false;
}

void Board::switch_players() {
    currentPlayer = Board::opponent();
}

char Board::get_player() {
    return currentPlayer;
}

Board::Move::Move(int _h, int _w) : h(_h), w(_w) {}

Board::Score::Score(int _b, int _w): black(_b), white(_w) {}

void Board::get_board_state(char (&b)[BOARD_SIZE][BOARD_SIZE]) {
    for(int i = 0; i < BOARD_SIZE; i++)
        for(int j = 0; j < BOARD_SIZE; j++)
            b[i][j] = board[i][j];
}

Board::Score Board::get_result() {
    int b = 0, w = 0;
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            char cell = board[i][j];
            if(cell == BLACK) b++;
            else if(cell == WHITE) w++;
        }
    }
    return Score(b, w);
}