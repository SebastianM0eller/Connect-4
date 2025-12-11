//
// Created by sebastian on 12/8/25.
//

#pragma once
#include <map>

// An enum class that represents the different states of a tile
enum class TileState
{
  Empty,
  Player1,
  Player2
};

class GameBoard
{
public:
  GameBoard();
  ~GameBoard() = default;

  void printBoard() const;
  void editBoard(int column, TileState state);

  [[nodiscard]] bool hasPlayerWon(int column, TileState state) const;
  [[nodiscard]] bool isBoardFull() const; // Is it a draw?
  [[nodiscard]] bool isColumnFull(int column) const;

private:
  static constexpr int m_rows {6};
  static constexpr int m_columns {7};
  // [Rows][Columns]
  // Initializes to 'Empty'
  TileState m_GameBoard[m_rows][m_columns];
  std::map<int, bool> m_availableColumns;

  // Helper function for printBoard
  static char getTileChar(TileState state);

  [[nodiscard]] bool horizontalWin(int column, int row, TileState state) const;
  [[nodiscard]] bool verticalWin(int column, int row, TileState state) const;
  [[nodiscard]] bool diagonalWin(int column, int row, TileState state) const;

  [[nodiscard]] int countDirection(int startColumn, int startRow, int colDirection, int rowDirection, TileState state) const;
};
