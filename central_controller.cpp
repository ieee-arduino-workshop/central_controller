// TODO :  Feature - draw player dynamically when adding more players
#include "GameManager.h"

using namespace std;

int main() {
    GameManager* g = new GameManager(70, 20, 6);

    g->run();

    return 0;
}