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

  void makeMove() const;
  TileState getSymbol() const { return m_state; }

private:
  GameBoard& m_gameBoard;
  const TileState m_state;

  // Returns 0 if there are no winning moves
  int canWin() const;
  int playerCanWin() const;

  // Returns a random valid move.
  int pickRandomMove() const;
};