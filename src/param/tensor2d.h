#ifndef OTHELLO_MINI_TENSOR2D_H
#define OTHELLO_MINI_TENSOR2D_H

#include "base.h"

template <typename T>
class Tensor2d: public Param {
private:
    int h;
    int w;
    T **arr;

public:
    Tensor2d(int _h, int _w);
    ~Tensor2d();

    void print();
    bool read(ifstream &fin);
    bool write(ofstream &fout);

    T *operator[](int i);
};

template class Tensor2d<int>;
template class Tensor2d<float>;
template class Tensor2d<double>;

#endif //OTHELLO_MINI_TENSOR2D_H
