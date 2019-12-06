#include "tensor2d.h"
#include <iostream>
using namespace std;

template <typename T>
Tensor2d<T>::Tensor2d(int _h, int _w): h(_h), w(_w) {
    arr = new T*[h];
    for(int i = 0; i < h; i++) {
        arr[i] = new T[w];
        for(int j = 0; j < w; j++) {
            arr[i][j] = 0;
        }
    }
}

template <typename T>
Tensor2d<T>::Tensor2d(Tensor2d &t): h(t.h), w(t.w) {
    arr = new T*[h];
    for(int i = 0; i < h; i++) {
        arr[i] = new T[w];
        for(int j = 0; j < w; j++) {
            arr[i][j] = t[i][j];
        }
    }
}

template <typename T>
Tensor2d<T>::~Tensor2d() {
    for(int i = 0; i < h; i++) {
        delete[] arr[i];
    }
    delete[] arr;
}

template <typename T>
T* Tensor2d<T>::operator[](int i) {
    if(i < 0 || h <= i) throw "index exceeded array length";
    return arr[i];
}

template <typename T>
void Tensor2d<T>::print() {
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            cout << arr[i][j] << "\t";
        }
        cout << endl;
    }
}

template <typename T>
bool Tensor2d<T>::read(ifstream &fin) {
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            fin >> arr[i][j];
            if(fin.fail()) {
                cout << "File format wrong" << endl;
                return false;
            }
        }
    }
    return true;
}

template <typename T>
bool Tensor2d<T>::write(ofstream &fout) {
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            fout << arr[i][j] << "\t";
        }
        fout << endl;
    }
    return true;
}
