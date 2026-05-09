#ifndef GAMEUI_H
#define GAMEUI_H

#include <SFML/Graphics.hpp>
#include "GameLogic.h"
#include <string>

class GameUI {
public:
    GameUI();
    
    bool isOpen() const;
    void clear();
    void display();
    void close();
    sf::RenderWindow& getWindow();

    void drawBoard(const GameLogic& game, int activeBotMode);
    void drawGameOverOverlay();
    void drawWinOverlay();

private:
    sf::RenderWindow window;
    sf::Font font;
    
    sf::Color getTileColor(int value);
    sf::Color getTextColor(int value);
};

#endif