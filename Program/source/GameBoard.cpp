//
// Created by sebastian on 12/8/25.
//

#include "GameBoard.h"
#include <iostream>

GameBoard::GameBoard()
{
  // Go through each element in out gameboard, as set the value to Empty
  for (int column {0}; column < 7; column++)
  {
    for (int row {0}; row < 6; row++)
    {
      m_GameBoard[row][column] = TileState::Empty;
    }

    // For each column in the gameboard, we add it to the available moves
    // We add one, so that we don't start counting at 0
    m_availableColumns.push_back(column + 1);
  }
}

// Prints the current status of the board
void GameBoard::printBoard() const
{

  for (const auto & row : m_GameBoard)
  {
    for (const auto column : row)
    {
      std::cout << getTileChar(column) << " ";
    }
    std::cout << std::endl;
  }
  for (int column {1}; column <= m_columns; column++)
    std::cout << column << " ";

  std::cout << std::endl << std::endl;
}

// Make a play to the board
// Takes in the column the player wants to play, as well as the TileState for that player
void GameBoard::placeInBoard(int column, const TileState state)
{
  // we transform the column to 0-index
  column--;

  // We start at the bottom of the board
  int row {m_rows - 1};

  // We keep moving up, as long as the tile is not empty
  while (m_GameBoard[row][column] != TileState::Empty)
  { row--; }

  // When we have found our tile, we set it to the new state from the player
  m_GameBoard[row][column] = state;

  // We check if it was the last available place in that column (row = 0)
  // If it is, we remove the column from the available columns
  if (row == 0) {std::erase(m_availableColumns, column);}
}

// Returns a char, based on the state argument
char GameBoard::getTileChar(const TileState state)
{
  switch (state)
  {
  case TileState::Empty:
    return '-';
  case TileState::Player1:
    return 'X';
  case TileState::Player2:
    return 'O';
  }
  return '?';
}

// A function to check if the player has won
bool GameBoard::hasPlayerWon(int column, const TileState state) const
{
  // Transform the to begin at 1 instead of 0
  column--;
  std::cout << column << std::endl;
  printBoard();
  // A player should not have an Empty state
  if (state == TileState::Empty)
  {
    std::cerr << "Invalid state for hasPlayerWon" << std::endl;
    return false;
  }

  // Find the exact location the player played
  // We start at the top and move down until
  // we find the location the player played
  int row {0};
  while (m_GameBoard[row][column] != state)
  { row++; }

  // As the AI check all column, we need a safeguard in case we don't hit

  // Check the horizontal winning condition
  if (horizontalWin(column, row, state)) { return true; }

  // Check vertical winning condition
  if (verticalWin(column, row, state)) { return true; }

  // Check the diagonal winning condition
  if (diagonalWin(column, row, state)) { return true; }

  return false;
}

// Returns true if there are no values in the available column
bool GameBoard::isBoardFull() const
{
  if (m_availableColumns.empty()) { return true; }
  return false;
}

// Return true of the column is in the available columns
bool GameBoard::isMoveValid(const int column) const
{
  return std::ranges::find(m_availableColumns, column) != m_availableColumns.end();
}


// Check if there is a horizontal winning condition
bool GameBoard::horizontalWin(const int column, const int row, const TileState state) const
{
  int inLine {1};
  inLine += countDirection(column, row, 1, 0, state);
  inLine += countDirection(column, row, -1, 0, state);

  return inLine >= 4;
}

// Check if there is a vertical winning condition
bool GameBoard::verticalWin(const int column, const int row, const TileState state) const
{
  int inLine {1};
  inLine += countDirection(column, row, 0, 1, state);
  inLine += countDirection(column, row, 0, -1, state);

  return inLine >= 4;
}

// Check if there is a diagonal winning condition
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

// A helper function used to check for win conditions
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
