#include "human.h"
#include "../utils.h"
#include <iostream>
using namespace std;

Human::Human(char _player) {
    player = _player;
}

Board::Move Human::make_move(char board[BOARD_SIZE][BOARD_SIZE]) {
    print_board(board);
    cout << "It is " << (player == WHITE ? "white" : "black") << "'s turn! Play your move (h, w): ";
    int h, w;
    cin >> h >> w;
    while (cin.fail()) {
        cout << "h and w has to be integer values between 0-7, separated by a space. Try again: ";
        cin.clear();
        cin.ignore(10000, '\n');
        cin >> h >> w;
    }
    Board::Move move(h, w);
    return move;
}

void Human::apply_reward(double reward, bool final) {
    if(!final && reward < 0) {
        cout << "Whoops! Made a mistake!" << endl;
    }
}
