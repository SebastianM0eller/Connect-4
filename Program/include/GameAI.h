//
// Created by sebastian on 12/12/25.
//

#pragma once
#include "GameBoard.h"

class GameAI
{
public:
  GameAI(GameBoard& gameBoard, TileState state);
  ~GameAI() = default;

  [[nodiscard]] int getMove() const;
  [[nodiscard]] TileState getState() const { return m_state; }

private:
  GameBoard& m_gameBoard;
  const TileState m_state;

  // Returns 0 if there are no winning moves
  [[nodiscard]] int canWin() const;
  [[nodiscard]] int playerCanWin() const;

  // Returns a random valid move.
  [[nodiscard]] int pickRandomMove() const;
};