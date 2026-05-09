#ifndef GAMELOGIC_H
#define GAMELOGIC_H

class GameLogic {
public:
    GameLogic(); 
    void reset();

    bool moveUp();
    bool moveDown();
    bool moveLeft();
    bool moveRight();

    bool isGameOver() const;
    bool hasWon() const;
    void continuePlaying();

    void saveGame() const;
    void loadGame();

    int getTile(int row, int col) const;
    int getScore() const;

private:
    int board[4][4];
    int score;
    bool keepPlayingAfterWin;

    void addRandomTile();
};

#endif