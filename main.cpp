#include "GameLogic.h"
#include "GameUI.h"
#include "GameController.h"
#include <ctime>
#include <cstdlib>

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    GameLogic game;
    GameUI ui;
    GameController controller(game, ui);

    controller.run();

    return 0;
}