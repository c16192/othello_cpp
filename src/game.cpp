#include "game.h"
#include "const.h"
#include "agent/human.h"
#include <iostream>
using namespace std;

Game::Game(Agent *black, Agent *white, bool _comment) {
    agents[0] = black;
    agents[1] = white;
    comment = _comment;
}

void Game::play() {
    while(!passed[0] || !passed[1]) {
        Game::play_turn();
    }
    Board::Score score = board.get_result();
    if(comment) {
        cout << "Game Over! Black: " << score.black << ", White: " << score.white << endl;
    }
    double reward_b;
    if (score.black > score.white) {
        reward_b = 1.0;
    } else if (score.black < score.white) {
        reward_b = -1.0;
    } else {
        reward_b = 0.0;
    }
    agents[0]->apply_reward(reward_b, true);
    agents[1]->apply_reward(-reward_b, true);
}

void Game::play_turn() {
    if(comment) {
        board.print();
        cout << endl;
    }
    Agent *agent = Game::currentAgent();
    bool pass = !board.exist_moves();
    passed[board.get_player() == WHITE] = pass;
    if(pass) {
        if(comment) {
            cout << (board.get_player() == WHITE ? "White" : "Black") << " cannot play!" << endl;
        }
        board.switch_players();
        return;
    }
    bool success = false;
    do {
        char b[BOARD_SIZE][BOARD_SIZE];
        board.get_board_state(b);
        Board::Move move = (*agent).make_move(b);
        success = board.make_move(move);
        if(!success) (*agent).apply_reward(-1.0, false);
    } while (!success);
}

Agent *Game::currentAgent() {
    return agents[board.get_player() == WHITE];
}