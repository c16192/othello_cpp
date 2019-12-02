#include <iostream>
#include "board.h"
using namespace std;


int main() {
    Board board;
    board.print();
    for(int i = 0; i < 10; i++) {
        int h, w;
        cin >> h >> w;
        bool success = board.make_move(h, w);
        cout << success << endl;
        board.print();
    }
    return 0;
}
