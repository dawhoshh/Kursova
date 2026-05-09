#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "GameLogic.h"
#include "GameUI.h"
#include "Bot.h"

class GameController {
public:
    GameController(GameLogic& logic, GameUI& ui);
    void run();

private:
    void handleEvents();
    void updateBot();

    GameLogic& game;
    GameUI& ui;
    
    int activeBotMode; // 0 - Гравець, 1 - Жадібний, 2 - Монте-Карло
    Bot* activeBot;
    GreedyBot greedyBot;
    MonteCarloBot monteCarloBot;
    
    sf::Clock botTimer;
};

#endif