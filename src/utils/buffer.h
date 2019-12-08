#ifndef OTHELLO_MINI_BUFFER_H
#define OTHELLO_MINI_BUFFER_H

template <class T>
class ReplayBuffer {
private:
    T *buffer;
    int head = 0;

public:
    int size;
    int count = 0;
    ReplayBuffer(int _size): size(_size) {
        buffer = new T[size];
    }
    ~ReplayBuffer() {
        delete[] buffer;
    }
    void push(T item) {
        buffer[head] = item;
        if(!ReplayBuffer::full()) count++;
        head = (head + 1) % size;
    }
    T sample() {
        return buffer[rand() % count];
    }
    T last() {
        return buffer[(head + size - 1) % size];
    }
    bool full() {
        return count == size;
    }
};

#endif //OTHELLO_MINI_BUFFER_H
