#include "dqn.h"
#include "../utils.h"
#include <iostream>
#include <cstring>
#include <ctime>
using namespace std;

DQN::DQN(char _player) {
    player = _player;
    memory = new ReplayBuffer<Experience>(256);

    model = Net();

    try {
        torch::load(model, "../model/" + string(1, player) + ".pt");
    } catch(const exception &e) {}

    optimizer = new torch::optim::Adam(model->parameters(), torch::optim::AdamOptions(1e-3));
    action = torch::zeros({2});

}

DQN::~DQN() {
    torch::save(model, "../model/" + string(1, player) + ".pt");
    delete memory;
    delete optimizer;
}

Board::Move DQN::make_move(char board[BOARD_SIZE][BOARD_SIZE]){
    torch::Tensor state_new = DQN::board_to_state(board);
    if(!is_first_round) {
        Experience e(state, action, reward, state_new);
        memory->push(e);
    }
    is_first_round = false;
    state = state_new;

    DQN::update_q();
    DQN::decide_action();

    return DQN::action_to_move();
}

Board::Move DQN::action_to_move() {
    return {action[0].item<int>(), action[1].item<int>()};
}

torch::Tensor DQN::board_to_state(char board[BOARD_SIZE][BOARD_SIZE]){
    torch::Tensor state = torch::empty({BOARD_SIZE, BOARD_SIZE});
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            double value = -1;
            if(board[i][j] == EMPTY) value = 0;
            else if(board[i][j] == player) value = 1;
            state[i][j] = value;
        }
    }
    return state.view({1, 1, BOARD_SIZE, BOARD_SIZE});
}

void DQN::apply_reward(double _reward, bool final) {
    reward = _reward;
    if(final) reward *= 10;
    cum_reward += reward;
    Experience e(state, action, reward, state, false);
    memory->push(e);
    if(final) {
        completed_episodes++;
        cout << (player == WHITE ? "Black" : "White") << " got cumulative reward of: " << cum_reward << endl;
        cum_reward = 0.0;
    }
}

void DQN::update_q() {
    if(!memory->count) return;

    torch::Tensor states, loss, target_value, predicted_value;
    double next_value;
    int BATCH_SIZE = min(memory->count, 64);

    Experience e = memory->last();
    model->eval();
    target_value = torch::zeros({BATCH_SIZE});
    states = torch::empty({BATCH_SIZE, 1, BOARD_SIZE, BOARD_SIZE});
    for(int i = 0; i < BATCH_SIZE; i++) {
        next_value = e.exists_state_next ? model->forward(e.state_next).max().item<double>() : 0.0;
        target_value[i] = e.reward + gamma * next_value;
        states[i] = e.state[0];
        e = memory->sample();
    }

    model->train();
    optimizer->zero_grad();

    predicted_value = model->forward(states).permute({1, 2, 3, 0})[0][action[0].item<int>()][action[1].item<int>()];

    loss = torch::pow(predicted_value - target_value, 2).mean();
//        cout << loss << " " << e.reward << " " << predicted_value << " " << target_value << endl;
    loss.backward();
    optimizer->step();
}

void DQN::decide_action() {
    model->eval();
    torch::Tensor prob = model->forward(state).exp().flatten();

    double r = ((double) rand() / (RAND_MAX)) * prob.sum().item<double>();
    double sum = 0.0;
    int i;
    for(i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
        sum += prob[i].item<double>();
        if(sum >= r) break;
    }
    action[0] = int(i / BOARD_SIZE);
    action[1] = i % BOARD_SIZE;
}

void DQN::print() {
    if(is_first_round) return;
    cout <<  model->forward(state).exp() << endl;
}