#ifndef OTHELLO_CPP_DQN_H
#define OTHELLO_CPP_DQN_H

#include "base.h"
#include "model.h"
#include "../const.h"
#include "../utils/buffer.h"
#include <torch/torch.h>
#include "../utils/experience.h"

template class ReplayBuffer<Experience>;

class DQN: public Agent {
private:
    double gamma = 0.9;
    torch::nn::Sequential model;
    torch::optim::Adam *optimizer;
    torch::Tensor state;
    torch::Tensor action;
    double reward;
    bool is_first_round = true;
    int completed_episodes = 0;
    ReplayBuffer<Experience> *memory;
    torch::Tensor board_to_state(char board[BOARD_SIZE][BOARD_SIZE]);
    void update_q();
    void decide_action();
    Board::Move action_to_move();

public:
    DQN(char _player);
    ~DQN();
    Board::Move make_move(char board[BOARD_SIZE][BOARD_SIZE]);
    void apply_reward(double _reward, bool final);
    void print();
};


#endif //OTHELLO_CPP_DQN_H
