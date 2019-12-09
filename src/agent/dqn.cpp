#include "dqn.h"
#include "../utils.h"
#include <iostream>
using namespace std;

DQN::DQN(char _player) {
    player = _player;
    memory = new ReplayBuffer<Experience>(64);
    model = Net();
    optimizer = new torch::optim::Adam(model->parameters(), torch::optim::AdamOptions(1e-3));
    action = torch::zeros({2});
}

DQN::~DQN() {
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
    return Board::Move(action[0].item<int>(), action[1].item<int>());
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
//    if(!final && reward < 0) {
//        cout << "Whoops! Made a mistake!" << "(" << action[0].item<int>() << " " << action[1].item<int>() << ")" << endl;
//    }
    Experience e(state, action, reward, state, false);
    memory->push(e);
    if(final) {
        completed_episodes++;
    }
}

void DQN::update_q() {
    if(!memory->full()) return;
    torch::Tensor loss, output, next_value, target_value, predicted_value;
    Experience e = memory->last();
    int BATCH_SIZE = 4;
    for(int i = 0; i < BATCH_SIZE; i++) {
        model->eval();
        next_value = torch::zeros({1, 1});
        if(e.exists_state_next) {
            next_value = model->forward(e.state_next).max().view({-1, 1});
        }

        target_value = e.reward + gamma * next_value;

        model->train();

        optimizer->zero_grad();

        output = model->forward(e.state);
        predicted_value = output[0][0][action[0].item<int>()][action[1].item<int>()].view({-1, 1});

        loss = torch::pow(predicted_value - target_value, 2);
//        cout << loss << " " << e.reward << " " << predicted_value << " " << target_value << endl;
        loss.backward();
        optimizer->step();
        e = memory->sample();
    }
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