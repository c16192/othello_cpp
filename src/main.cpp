#include <iostream>
#include "game.h"
#include "agent/human.h"
#include "agent/dqn.h"
#include <torch/torch.h>
#include <ctime>
using namespace std;


int main() {
    Human human(BLACK);
    DQN player_w(BLACK);
    DQN player_b(WHITE);
    for(int i = 0; i < 100; i++) {
        cout << "Game " << i << " started!" << endl;
        clock_t begin = clock();

        Game game(&player_b, &player_w, false);
        game.play();

        clock_t end = clock();
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

        cout << "Game " << i << " took " << elapsed_secs << " sec" << endl;
    }
    while(true) {
        Game game(&human, &player_w, true);
        game.play();
    }
}
