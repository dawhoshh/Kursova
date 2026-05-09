#ifndef BOT_H
#define BOT_H

#include "GameLogic.h"

enum class MoveDirection {
    Up,
    Down,
    Left,
    Right,
    None
};


class Bot {
public:
    virtual MoveDirection getBestMove(GameLogic gameCopy) = 0;

    // Віртуальний деструктор
    virtual ~Bot() = default;
};

// Бот 1: Жадібний алгоритм
class GreedyBot : public Bot {
public:
    MoveDirection getBestMove(GameLogic gameCopy) override;
};

// Бот 2: Метод Монте-Карло
class MonteCarloBot : public Bot {
public:
    MoveDirection getBestMove(GameLogic gameCopy) override;
};

#endif
