//
// Created by sebastian on 12/11/25.
//

#include "Game.h"

#include <iostream>
#include <limits>

Game::Game()
  : m_gameBoard() {}

void Game::Run()
{
  m_gameOver = false;

  while (!m_gameOver)
  {
    clearConsole();
    // Print the current board, so the player has some context
    printStatus();

    // Make the play
    int column = getMove();
    m_gameBoard.editBoard(column, m_currentPlayer);

    if (checkGameStatus(column))
    { break; }

    switchPlayer();
  }
}

void Game::clearConsole()
{
  std::cout << std::string(100, '\n');
}

void Game::printStatus()
{
  m_gameBoard.printBoard();
  std::cout << "The current player is Player" << static_cast<int>(m_currentPlayer) << std::endl;
}

int Game::getMove() const
{
  std::cout << "Enter the column ou want to play: ";
  int column {0};

  // Keep trying to get an input until you get a valid input
  while (true)
  {
    // Check if the input you get is an integer
    if (std::cin >> column)
    {
      // Check if the integer is valid
      if (m_gameBoard.isMoveValid(--column))
      {
        return column;
      }

      std::cout << "Invalid move. Please enter a valid tile number: ";
    }
    // If the input isn't an int
    else
    {
      std::cout << "Invalid input. Please enter a number." << std::endl;

      // Reset the input
      std::cin.clear();
      // Clear the buffer
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
}

bool Game::checkGameStatus(const int column)
{
  if (m_gameBoard.hasPlayerWon(column, m_currentPlayer))
  {
    m_gameOver = true;
    std::cout << "Player 1 wins!" << std::endl;
    return true;
  }

  if (m_gameBoard.isBoardFull())
  {
    m_gameOver = true;
    std::cout << "Draw!" << std::endl;
    return true;
  }

  return false;
}

void Game::switchPlayer()
{
  m_currentPlayer = (m_currentPlayer == TileState::Player1) ? TileState::Player2 : TileState::Player1;
}