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
  TileState m_Player1 {TileState::Player1};
  TileState m_Player2 {TileState::Player2};
  TileState m_currentPlayer {TileState::Player1};

  void singlePlayerGame();
  void multiPlayerGame();

  bool m_gameOver {false};

  static void clearConsole();
  void printStatus();
  [[nodiscard]] int getMove() const;
  bool checkGameStatus(int column);
  void switchPlayer();
};