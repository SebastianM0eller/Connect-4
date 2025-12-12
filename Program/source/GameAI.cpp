//
// Created by sebastian on 12/12/25.
//

#include "GameAI.h"
#include "Random.h"

GameAI::GameAI(GameBoard& gameBoard, const TileState state)
  : m_gameBoard(gameBoard), m_state(state) {}

void GameAI::makeMove() const
{
  if (canWin() != 0)
  { m_gameBoard.editBoard(canWin(), m_state); }

  else if (playerCanWin() != 0)
  { m_gameBoard.editBoard(playerCanWin(), m_state); }

  else { m_gameBoard.editBoard(pickRandomMove(), m_state); }
}

int GameAI::canWin() const
{
  for (const int column : m_gameBoard.getAvailableColumns())
  {
    GameBoard copy = m_gameBoard;
    copy.editBoard(column, m_state);
    if (copy.hasPlayerWon(column, m_state)) { return column; }
  }
  return 0;
}

int GameAI::playerCanWin() const
{
  const TileState playerSymbol = (m_state == TileState::Player1) ? TileState::Player2 : TileState::Player1;
  for (const int column : m_gameBoard.getAvailableColumns())
  {
    GameBoard copy = m_gameBoard;
    copy.editBoard(column, playerSymbol);
    if (copy.hasPlayerWon(column, playerSymbol)) { return column; }
  }
  return 0;
}

int GameAI::pickRandomMove() const
{
  const std::vector<int> moves = m_gameBoard.getAvailableColumns();
  const int move = Random::getRandomInt(0, moves.size() - 1);
  return moves[move];
}


