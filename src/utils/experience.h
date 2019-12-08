#ifndef OTHELLO_CPP_EXPERIENCE_H
#define OTHELLO_CPP_EXPERIENCE_H

#include <torch/torch.h>

class Experience {
public:
    torch::Tensor state;
    torch::Tensor action;
    double reward;
    torch::Tensor state_next;
    bool exists_state_next;
    Experience() {}
    Experience(torch::Tensor s, torch::Tensor a, double r, torch::Tensor s_next, bool exists_s_next=true):
        state(s), action(a), reward(r), state_next(s_next), exists_state_next(exists_s_next) {}
};


#endif //OTHELLO_CPP_EXPERIENCE_H
