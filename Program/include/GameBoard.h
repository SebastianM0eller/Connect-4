//
// Created by sebastian on 12/8/25.
//

#pragma once
#include <map>
#include <vector>

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
  // [Rows][Columns]
  // Initializes to 'Empty'
  TileState m_GameBoard[6][7] {};
  std::map<int, bool> m_availableColumns;

  // Helper function for printBoard
  static char getTileChar(TileState state);

  [[nodiscard]] bool horizontalWin(int column, int row, TileState state) const;
  [[nodiscard]] bool verticalWin(int column, int row, TileState state) const;
  [[nodiscard]] bool diagonalWin(int column, int row, TileState state) const;
};
