//
// Created by sebastian on 12/8/25.
//

#include "GameBoard.h"

#include <iostream>

GameBoard::GameBoard()
{
  for (int row {0}; row < 6; row++)
  {
    for (int column {0}; column < 7; column++)
    {
      m_GameBoard[row][column] = TileState::Empty;
      m_availableColumns[column] = true;
    }
  }
}

void GameBoard::printBoard() const
{
  for (const auto & row : m_GameBoard)
  {
    for (const auto column : row)
    {
      std::cout << getTileChar(column);
    }
    std::cout << std::endl;
  }
}

void GameBoard::editBoard(const int column, const TileState state)
{
  int row {5};
  while (m_GameBoard[row][column] != TileState::Empty)
  { row--; }

  m_GameBoard[row][column] = state;
  if (row == 0) {m_availableColumns[column] = false;}
}

bool GameBoard::hasPlayerWon(const int column, const TileState state) const
{
  if (state == TileState::Empty)
  { std::cerr << "Invalid state for hasPlayerWon" << std::endl; return false; }

  // Find the exact location the player played
  int row {0};
  while (m_GameBoard[row][column] != state)
  { row++; }

  // Check the horizontal winning condition
  if (horizontalWin(column, row, state)) { return true; }

  // Check vertical winning condition
  if (verticalWin(column, row, state)) { return true; }

  // Check the diagonal winning condition
  if (diagonalWin(column, row, state)) { return true; }

  return false;
}

bool GameBoard::isBoardFull() const
{
  for (auto column : m_availableColumns)
  { if (column.second) { return false; } }
  return true;
}

bool GameBoard::isMoveValid(const int column) const
{
  if (column < 0 || column >= m_columns) { return false; }
  return m_availableColumns.at(column);
}

char GameBoard::getTileChar(const TileState state)
{
  switch (state)
  {
    case TileState::Empty:
      return ' ';
    case TileState::Player1:
      return 'X';
    case TileState::Player2:
      return 'O';
  }
  return '?';
}

bool GameBoard::horizontalWin(const int column, const int row, const TileState state) const
{
  // We initialize as one to include the current square.
  int inLine {1};
  inLine += countDirection(column, row, 1, 0, state);
  inLine += countDirection(column, row, -1, 0, state);

  return inLine >= 4;
}

bool GameBoard::verticalWin(const int column, const int row, const TileState state) const
{
  int inLine {1};
  inLine += countDirection(column, row, 0, 1, state);
  inLine += countDirection(column, row, 0, -1, state);

  return inLine >= 4;
}

bool GameBoard::diagonalWin(const int column, const int row, const TileState state) const
{
  int inLine {1};
  inLine += countDirection(column, row, 1, 1, state);
  inLine += countDirection(column, row, -1, -1, state);

  if (inLine >= 4) { return true; }

  inLine = 1;
  inLine += countDirection(column, row, 1, -1, state);
  inLine += countDirection(column, row, -1, 1, state);

  return inLine >= 4;
}

int GameBoard::countDirection(const int startColumn, const int startRow, const int colDirection,
                              const int rowDirection, const TileState state) const
{
  int count {0};
  int row = startRow + rowDirection;
  int column = startColumn + colDirection;

  while ( 0 <= row && row < m_rows && 0 <= column && column < m_columns && m_GameBoard[row][column] == state)
  {
    count++;
    row += rowDirection;
    column += colDirection;
  }
  return count;
}
