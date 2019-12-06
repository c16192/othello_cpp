#ifndef OTHELLO_MINI_GAME_H
#define OTHELLO_MINI_GAME_H

#include "board.h"
#include "agent/base.h"

enum GameType {human2human, human2comp, comp2comp};

class Game {
private:
    bool comment;
    Agent *agents[2]; // black and white
    bool passed[2] = {false, false};
    Board board;
    Agent *currentAgent(void);
    void play_turn();

public:
    Game(Agent *black, Agent *white, bool _comment);
    void play();
};


#endif //OTHELLO_MINI_GAME_H
