#include <iostream>
#include "game.h"
#include "agent/human.h"
using namespace std;


int main() {
    Human player_b(BLACK);
    Human player_w(WHITE);
    Game game(&player_b, &player_w, true);
    game.play();
    return 0;
}
