#include "Bot.h"
#include <cstdlib>

//  Жадібний бот
MoveDirection GreedyBot::getBestMove(GameLogic gameCopy) {
    int bestScore = -1;
    MoveDirection bestMove = MoveDirection::None;

    GameLogic copyLeft = gameCopy;
    if (copyLeft.moveLeft() && copyLeft.getScore() > bestScore) {
        bestScore = copyLeft.getScore();
        bestMove = MoveDirection::Left;
    }

    GameLogic copyRight = gameCopy;
    if (copyRight.moveRight() && copyRight.getScore() > bestScore) {
        bestScore = copyRight.getScore();
        bestMove = MoveDirection::Right;
    }

    GameLogic copyUp = gameCopy;
    if (copyUp.moveUp() && copyUp.getScore() > bestScore) {
        bestScore = copyUp.getScore();
        bestMove = MoveDirection::Up;
    }

    GameLogic copyDown = gameCopy;
    if (copyDown.moveDown() && copyDown.getScore() > bestScore) {
        bestScore = copyDown.getScore();
        bestMove = MoveDirection::Down;
    }

    if (bestScore == 0 || bestScore == -1) {
        GameLogic test = gameCopy;
        if (test.moveLeft()) return MoveDirection::Left;
        if (test.moveRight()) return MoveDirection::Right;
        if (test.moveUp()) return MoveDirection::Up;
        if (test.moveDown()) return MoveDirection::Down;
    }
    return bestMove;
}

// Монте-Карло
MoveDirection MonteCarloBot::getBestMove(GameLogic gameCopy) {
    int runs = 50; // Скільки разів симулюємо гру для КОЖНОГО напрямку
    MoveDirection bestMove = MoveDirection::None;
    long long bestTotalScore = -1;

    MoveDirection directions[] = {MoveDirection::Left, MoveDirection::Right, MoveDirection::Up, MoveDirection::Down};

    for (MoveDirection firstMove: directions) {
        GameLogic firstStepCopy = gameCopy;
        bool validMove = false;


        if (firstMove == MoveDirection::Left) validMove = firstStepCopy.moveLeft();
        else if (firstMove == MoveDirection::Right) validMove = firstStepCopy.moveRight();
        else if (firstMove == MoveDirection::Up) validMove = firstStepCopy.moveUp();
        else if (firstMove == MoveDirection::Down) validMove = firstStepCopy.moveDown();

        if (!validMove) continue;

        long long totalScore = 0;


        for (int i = 0; i < runs; ++i) {
            GameLogic simulation = firstStepCopy;
            while (!simulation.isGameOver()) {
                int randomDir = std::rand() % 4;
                if (randomDir == 0) simulation.moveLeft();
                else if (randomDir == 1) simulation.moveRight();
                else if (randomDir == 2) simulation.moveUp();
                else if (randomDir == 3) simulation.moveDown();
            }
            totalScore += simulation.getScore();
        }

        if (totalScore > bestTotalScore) {
            bestTotalScore = totalScore;
            bestMove = firstMove;
        }
    }

    if (bestMove == MoveDirection::None) {
        GameLogic test = gameCopy;
        if (test.moveLeft()) return MoveDirection::Left;
        if (test.moveRight()) return MoveDirection::Right;
        if (test.moveUp()) return MoveDirection::Up;
        if (test.moveDown()) return MoveDirection::Down;
    }

    return bestMove;
}
