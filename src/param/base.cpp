#include "base.h"

bool Param::load(string fpath) {
    ifstream fin(fpath);
    bool success = false;
    if (fin.is_open()) {
        success = this->read(fin);
        fin.close();
    } else cout << "File \"" << fpath << "\" cannot be read" << endl;
    return success;
}

bool Param::save(string fpath) {
    ofstream fout(fpath);
    bool success = false;
    if(fout.is_open()) {
        success = this->write(fout);
        fout.close();
    } else cout << "Unable to open file \"" << fpath << "\"" << endl;
    return success;
}
