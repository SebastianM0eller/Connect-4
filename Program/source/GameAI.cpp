//
// Created by sebastian on 12/12/25.
//

#include "GameAI.h"

#include <iostream>
#include <ostream>

#include "Random.h"

GameAI::GameAI(GameBoard& gameBoard, const TileState state)
  : m_gameBoard(gameBoard), m_state(state) {}

int GameAI::getMove() const
{
  if (canWin() != 0)
  {
    return canWin();
  }

  if (playerCanWin() != 0)
  {
    return playerCanWin();
  }

  return pickRandomMove();
}

int GameAI::canWin() const
{
  for (const int column : m_gameBoard.getAvailableColumns())
  {
    GameBoard copy = m_gameBoard;
    copy.placeInBoard(column, m_state);

    if (copy.hasPlayerWon(column, m_state))
    {
      return column;
    }
  }
  return 0;
}

int GameAI::playerCanWin() const
{
  const TileState playerSymbol = (m_state == TileState::Player1) ? TileState::Player2 : TileState::Player1;
  for (const int column : m_gameBoard.getAvailableColumns())
  {

    GameBoard copy = m_gameBoard;
    copy.placeInBoard(column, playerSymbol);
    if (copy.hasPlayerWon(column, playerSymbol))
    {
      return column;
    }
  }
  return 0;
}

int GameAI::pickRandomMove() const
{
  std::cout << "Picking a random move" << std::endl;
  const std::vector<int> moves = m_gameBoard.getAvailableColumns();
  const int move = Random::getRandomInt(0, moves.size() - 1);
  return moves[move];
}


