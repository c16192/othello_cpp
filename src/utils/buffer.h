#ifndef OTHELLO_MINI_BUFFER_H
#define OTHELLO_MINI_BUFFER_H

template <class T>
class ReplayBuffer {
private:
    T *buffer;
    int size;
    int count = 0;
    int head = 0;

public:
    ReplayBuffer(int _size): size(_size) {
        buffer = new T[size];
    }
    ~ReplayBuffer() {
        delete[] buffer;
    }
    void push(T item) {
        buffer[head] = item;
        if(count < size) count++;
        head = (head + 1) % size;
    }
    T sample() {
        return buffer[rand() % count];
    }
};

#endif //OTHELLO_MINI_BUFFER_H
