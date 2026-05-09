#include "GameLogic.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>

GameLogic::GameLogic() {

    std::srand(std::time(nullptr));
    reset();
}

void GameLogic::reset() {
    score = 0;
    keepPlayingAfterWin = false;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            board[i][j] = 0;
        }
    }

    // Дві випадкові плитки на старті
    addRandomTile();
    addRandomTile();
}

void GameLogic::addRandomTile() {
    // 1. Де зараз нулі
    std::vector<std::pair<int, int> > emptyCells;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (board[i][j] == 0) {
                emptyCells.push_back({i, j});
            }
        }
    }

    if (emptyCells.empty()) return;

    // 2. Вибираю випадкову порожню клітинку зі знайдених
    int randomIndex = std::rand() % emptyCells.size();
    int row = emptyCells[randomIndex].first;
    int col = emptyCells[randomIndex].second;

    // 3. 2 (шанс 90%) або 4 (шанс 10%)
    board[row][col] = (std::rand() % 10 < 9) ? 2 : 4;
}

// для вікна
int GameLogic::getTile(int row, int col) const {
    return board[row][col];
}

int GameLogic::getScore() const {
    return score;
}

// ЛОГІКА РУХІВ

bool GameLogic::moveLeft() {
    bool boardChanged = false;

    for (int i = 0; i < 4; ++i) {
        // Крок 1: Зсуваю все вліво до упору, ігноруючи нулі
        int insertPos = 0;
        for (int j = 0; j < 4; ++j) {
            if (board[i][j] != 0) {
                if (j != insertPos) {
                    board[i][insertPos] = board[i][j];
                    board[i][j] = 0;
                    boardChanged = true;
                }
                insertPos++;
            }
        }

        // Крок 2: Злипання однакових сусідів
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] != 0 && board[i][j] == board[i][j + 1]) {
                board[i][j] *= 2;
                score += board[i][j];
                board[i][j + 1] = 0;
                boardChanged = true;
            }
        }

        // Крок 3: Фінальний зсув
        insertPos = 0;
        for (int j = 0; j < 4; ++j) {
            if (board[i][j] != 0) {
                if (j != insertPos) {
                    board[i][insertPos] = board[i][j];
                    board[i][j] = 0;
                }
                insertPos++;
            }
        }
    }

    //  нова плитка
    if (boardChanged) addRandomTile();
    return boardChanged;
}

bool GameLogic::moveRight() {
    bool boardChanged = false;
    for (int i = 0; i < 4; ++i) {
        int insertPos = 3;
        for (int j = 3; j >= 0; --j) {
            if (board[i][j] != 0) {
                if (j != insertPos) {
                    board[i][insertPos] = board[i][j];
                    board[i][j] = 0;
                    boardChanged = true;
                }
                insertPos--;
            }
        }
        for (int j = 3; j > 0; --j) {
            if (board[i][j] != 0 && board[i][j] == board[i][j - 1]) {
                board[i][j] *= 2;
                score += board[i][j];
                board[i][j - 1] = 0;
                boardChanged = true;
            }
        }
        insertPos = 3;
        for (int j = 3; j >= 0; --j) {
            if (board[i][j] != 0) {
                if (j != insertPos) {
                    board[i][insertPos] = board[i][j];
                    board[i][j] = 0;
                }
                insertPos--;
            }
        }
    }
    if (boardChanged) addRandomTile();
    return boardChanged;
}

bool GameLogic::moveUp() {
    bool boardChanged = false;
    for (int j = 0; j < 4; ++j) {
        //зовнішній цикл
        int insertPos = 0;
        for (int i = 0; i < 4; ++i) {
            // внутрішній
            if (board[i][j] != 0) {
                if (i != insertPos) {
                    board[insertPos][j] = board[i][j];
                    board[i][j] = 0;
                    boardChanged = true;
                }
                insertPos++;
            }
        }
        for (int i = 0; i < 3; ++i) {
            if (board[i][j] != 0 && board[i][j] == board[i + 1][j]) {
                board[i][j] *= 2;
                score += board[i][j];
                board[i + 1][j] = 0;
                boardChanged = true;
            }
        }
        insertPos = 0;
        for (int i = 0; i < 4; ++i) {
            if (board[i][j] != 0) {
                if (i != insertPos) {
                    board[insertPos][j] = board[i][j];
                    board[i][j] = 0;
                }
                insertPos++;
            }
        }
    }
    if (boardChanged) addRandomTile();
    return boardChanged;
}

bool GameLogic::moveDown() {
    bool boardChanged = false;
    for (int j = 0; j < 4; ++j) {
        int insertPos = 3;
        for (int i = 3; i >= 0; --i) {
            // По стовпцях знизу вгору
            if (board[i][j] != 0) {
                if (i != insertPos) {
                    board[insertPos][j] = board[i][j];
                    board[i][j] = 0;
                    boardChanged = true;
                }
                insertPos--;
            }
        }
        for (int i = 3; i > 0; --i) {
            if (board[i][j] != 0 && board[i][j] == board[i - 1][j]) {
                board[i][j] *= 2;
                score += board[i][j];
                board[i - 1][j] = 0;
                boardChanged = true;
            }
        }
        insertPos = 3;
        for (int i = 3; i >= 0; --i) {
            if (board[i][j] != 0) {
                if (i != insertPos) {
                    board[insertPos][j] = board[i][j];
                    board[i][j] = 0;
                }
                insertPos--;
            }
        }
    }
    if (boardChanged) addRandomTile();
    return boardChanged;
}

// СТАН ГРИ

bool GameLogic::isGameOver() const {
    // Кінець?
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (board[i][j] == 0) return false; // Ще є порожні місця
            if (i < 3 && board[i][j] == board[i + 1][j]) return false; // По вертикалі
            if (j < 3 && board[i][j] == board[i][j + 1]) return false; // По горизонталі
        }
    }
    return true;
}

bool GameLogic::hasWon() const {
    if (keepPlayingAfterWin) return false;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (board[i][j] == 2048) return true;
        }
    }
    return false;
}

void GameLogic::continuePlaying() {
    keepPlayingAfterWin = true;
}

// ЗБЕРЕЖЕННЯ І ЗАВАНТАЖЕННЯ

void GameLogic::saveGame() const {
    // Збереження у текст файл
    std::ofstream outFile("save.txt");
    if (outFile.is_open()) {
        outFile << score << " " << keepPlayingAfterWin << "\n";
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                outFile << board[i][j] << " ";
            }
            outFile << "\n";
        }
        outFile.close();
    }
}

void GameLogic::loadGame() {
    std::ifstream inFile("save.txt");
    if (inFile.is_open()) {
        inFile >> score >> keepPlayingAfterWin;
        bool isEmpty = true;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                inFile >> board[i][j];
                if (board[i][j] != 0) isEmpty = false;
            }
        }
        inFile.close();

        // Якщо файл виявився порожнім або пошкодженим - нове поле
        if (isEmpty) {
            reset();
        }
    }
}
