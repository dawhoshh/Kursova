#include "GameUI.h"

GameUI::GameUI() {
    window.create(sf::VideoMode({500, 650}), "2048", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    font.openFromFile("comicbd.ttf");
}

bool GameUI::isOpen() const { return window.isOpen(); }
void GameUI::clear() { window.clear(sf::Color(250, 248, 239)); }
void GameUI::display() { window.display(); }
void GameUI::close() { window.close(); }
sf::RenderWindow &GameUI::getWindow() { return window; }

sf::Color GameUI::getTileColor(int value) {
    switch (value) {
        case 0: return {205, 193, 180};
        case 2: return {238, 228, 218};
        case 4: return {237, 224, 200};
        case 8: return {242, 177, 121};
        case 16: return {245, 149, 99};
        case 32: return {246, 124, 95};
        case 64: return {246, 94, 59};
        case 128: return {237, 207, 114};
        case 256: return {237, 204, 97};
        case 512: return {237, 200, 80};
        case 1024: return {237, 197, 63};
        case 2048: return {237, 194, 46};
        default: return {60, 58, 50};
    }
}

sf::Color GameUI::getTextColor(int value) {
    if (value <= 4) return sf::Color(119, 110, 101);
    return sf::Color::White;
}

void GameUI::drawBoard(const GameLogic &game, int activeBotMode) {
    // 1. Заголовок
    sf::Text titleText(font, "2048", 70);
    titleText.setFillColor(sf::Color(119, 110, 101));
    titleText.setPosition({30.f, 20.f});
    window.draw(titleText);

    // 2. Рахунок
    sf::Text scoreText(font, "Score: " + std::to_string(game.getScore()), 35);
    scoreText.setFillColor(sf::Color(119, 110, 101));
    scoreText.setPosition({250.f, 30.f});
    window.draw(scoreText);

    // 3. Підказка під рахунком
    sf::Text restartText(font, "Press 'R' to restart", 20);
    restartText.setFillColor(sf::Color(119, 110, 101));
    restartText.setPosition({250.f, 75.f});
    window.draw(restartText);

    // 4. Текст з режимами бота
    sf::Text modeHintsText(font, "0:You | 1:Greedy | 2:Monte Carlo", 16);
    modeHintsText.setFillColor(sf::Color(119, 110, 101));
    modeHintsText.setPosition({20.f, 130.f});
    window.draw(modeHintsText);

    // 5. Підсвічений активний режим
    std::string activeStr = "Active: You";
    if (activeBotMode == 1) activeStr = "Active: Greedy";
    if (activeBotMode == 2) activeStr = "Active: Monte Carlo";

    sf::Text activeModeText(font, activeStr, 18);
    activeModeText.setFillColor(sf::Color(246, 94, 59));
    activeModeText.setPosition({300.f, 128.f});
    window.draw(activeModeText);

    // 6. Відмальовування плиток
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            int val = game.getTile(i, j);

            sf::RectangleShape tile({100.f, 100.f});
            tile.setPosition({30.f + j * 110.f, 170.f + i * 110.f});
            tile.setFillColor(getTileColor(val));
            window.draw(tile);

            if (val != 0) {
                sf::Text tileText(font, std::to_string(val), val > 512 ? 35 : 45);
                tileText.setFillColor(getTextColor(val));

                sf::FloatRect textRect = tileText.getLocalBounds();
                tileText.setOrigin({
                    textRect.position.x + textRect.size.x / 2.0f,
                    textRect.position.y + textRect.size.y / 2.0f
                });
                tileText.setPosition({tile.getPosition().x + 50.f, tile.getPosition().y + 50.f});

                window.draw(tileText);
            }
        }
    }
}

void GameUI::drawGameOverOverlay() {
    sf::RectangleShape overlay({500.f, 650.f});
    overlay.setFillColor(sf::Color(119, 110, 101, 180));
    window.draw(overlay);

    sf::Text gameOverText(font, "GAME OVER!\nPress R to restart", 40);
    gameOverText.setFillColor(sf::Color::White);

    gameOverText.setPosition({80.f, 280.f});
    window.draw(gameOverText);
}

void GameUI::drawWinOverlay() {
    sf::RectangleShape overlay({500.f, 650.f});
    overlay.setFillColor(sf::Color(237, 194, 46, 150));
    window.draw(overlay);

    sf::Text winText(font, "YOU WIN!\nPress C to continue", 40);
    winText.setFillColor(sf::Color::White);
    winText.setPosition({80.f, 250.f});
    window.draw(winText);
}
