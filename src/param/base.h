#ifndef OTHELLO_MINI_PARAM_BASE_H
#define OTHELLO_MINI_PARAM_BASE_H

#include <fstream>
#include <string>
#include <iostream>
using namespace std;

class Param {
public:
    bool load(string fpath);
    bool save(string fpath);
    virtual void print() = 0;
    virtual bool read(ifstream &fin) = 0;
    virtual bool write(ofstream &fout) = 0;
};

#endif //OTHELLO_MINI_PARAM_BASE_H
