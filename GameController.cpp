#include "GameController.h"

GameController::GameController(GameLogic& logic, GameUI& ui) 
    : game(logic), ui(ui), activeBotMode(0), activeBot(nullptr) {
    game.loadGame();
}

void GameController::run() {
    while (ui.isOpen()) {
        handleEvents();
        updateBot();

        ui.clear();
        ui.drawBoard(game, activeBotMode);

        if (game.isGameOver()) {
            ui.drawGameOverOverlay();
        } else if (game.hasWon()) {
            ui.drawWinOverlay();
        }

        ui.display();
    }
}

void GameController::handleEvents() {
    while (const std::optional<sf::Event> event = ui.getWindow().pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            game.saveGame();
            ui.close();
        }

        if (const auto* keyPress = event->getIf<sf::Event::KeyPressed>()) {
            // Перемикання режимів
            if (keyPress->code == sf::Keyboard::Key::Num0) { activeBotMode = 0; activeBot = nullptr; }
            if (keyPress->code == sf::Keyboard::Key::Num1) { activeBotMode = 1; activeBot = &greedyBot; }
            if (keyPress->code == sf::Keyboard::Key::Num2) { activeBotMode = 2; activeBot = &monteCarloBot; }
            
            // Сервісні клавіші
            if (keyPress->code == sf::Keyboard::Key::R) { game.reset(); }
            if (keyPress->code == sf::Keyboard::Key::C && game.hasWon()) { game.continuePlaying(); }

            // Ручне управління (тільки якщо бот вимкнений і гра не закінчена)
            if (activeBotMode == 0 && !game.isGameOver() && !game.hasWon()) {
                if (keyPress->code == sf::Keyboard::Key::Left) game.moveLeft();
                else if (keyPress->code == sf::Keyboard::Key::Right) game.moveRight();
                else if (keyPress->code == sf::Keyboard::Key::Up) game.moveUp();
                else if (keyPress->code == sf::Keyboard::Key::Down) game.moveDown();
            }
        }
    }
}

void GameController::updateBot() {
    if (activeBot != nullptr && !game.isGameOver() && !game.hasWon()) {
        if (botTimer.getElapsedTime().asSeconds() > 0.15f) {
            MoveDirection move = activeBot->getBestMove(game);
            
            if (move == MoveDirection::Left) game.moveLeft();
            else if (move == MoveDirection::Right) game.moveRight();
            else if (move == MoveDirection::Up) game.moveUp();
            else if (move == MoveDirection::Down) game.moveDown();
            
            botTimer.restart();
        }
    }
}