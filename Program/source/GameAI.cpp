//
// Created by sebastian on 12/12/25.
//

#include "GameAI.h"

#include <iostream>
#include <ostream>

#include "Random.h"

GameAI::GameAI(GameBoard& gameBoard, const TileState state)
  : m_gameBoard(gameBoard), m_state(state) {}

int GameAI::makeMove()
{
  if (canWin() != 0)
  {
    m_gameBoard.placeInBoard(canWin(), m_state);
    return canWin();
  }

  if (playerCanWin() != 0)
  {
    m_gameBoard.placeInBoard(playerCanWin(), m_state);
    return playerCanWin();
  }

  const int move = pickRandomMove();
  m_gameBoard.placeInBoard(move, m_state);
  return move;

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
  for (const int column : m_gameBoard.getAvailableColumns())
  {std::cout << column << " "; }
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


