//
// Created by sebastian on 12/11/25.
//

#pragma once
#include "GameBoard.h"

class Game
{
public:
  Game();
  ~Game() = default;

  void Run();

private:
  GameBoard m_gameBoard;
  TileState m_currentPlayer {TileState::Player1};

  bool m_gameOver {false};

  static void clearConsole();
  void printStatus();
  [[nodiscard]] int getMove() const;
  bool checkGameStatus(int column);
  void switchPlayer();
};