//
// Created by sebastian on 12/11/25.
//

#include "Game.h"
#include "GameAI.h"
#include "Random.h"
#include <iostream>

Game::Game()
  : m_gameBoard() {}

void Game::Run()
{
  int gameSelect {0};
  std::cout << "Welcome to Connect-4!\n";
  std::cout << "Would you like to play against the AI or against a friend? (1/2)\n";
  std::cin >> gameSelect;

  if (gameSelect == 2) { multiPlayerGame(); }
  else { singlePlayerGame(); }
}

void Game::multiPlayerGame()
{
  // Start by setting the game to be ongoing
  m_gameOver = false;

  // Run the game loop
  while (!m_gameOver)
  {
    // Clear and print the setup, so the player has context for the move
    clearConsole();
    printStatus();

    // Get the move from the player
    const int column = getMove();
    m_gameBoard.placeInBoard(column, m_currentPlayer);

    // Check if the game should stop
    if (checkGameStatus(column))
    { break; }

    // Now repeat, but for the other player
    switchPlayer();
  }
}

void Game::singlePlayerGame()
{
  // Start by creating the AI
  GameAI ai(m_gameBoard, m_currentPlayer);

  // Set the game to be ongoing
  m_gameOver = false;

  // Switch the current player at random, so both the player and AI can start.
  if (Random::getRandomInt(0,1) == 0)
  { switchPlayer(); }

  // Run the game loop
  while (!m_gameOver)
  {
    // If the AI is the current player, we run its game loop
    if (ai.getState() == m_currentPlayer)
    {
      // For debug
      std::cout << "Its the AI's Turn";
      // Get the move from the AI
      const int playedColumn = ai.getMove();
      m_gameBoard.placeInBoard(playedColumn, m_currentPlayer);
      if (checkGameStatus(playedColumn))
      {break;}
      switchPlayer();
    }
    else
    {
      clearConsole();
      printStatus();
      const int playedColumn = getMove();
      m_gameBoard.placeInBoard(playedColumn, m_currentPlayer);
      if (checkGameStatus(playedColumn))
      {break;}
      switchPlayer();
    }
  }
}

void Game::clearConsole()
{
  std::cout << std::string(100, '\n');
}

void Game::printStatus()
{
  m_gameBoard.printBoard();
  std::cout << "The current player is Player" << static_cast<int>(m_Player1) << std::endl;
}

int Game::getMove() const
{
  std::cout << "Enter the column you want to play: ";
  int column {0};

  // Keep trying to get an input until you get a valid input
  while (true)
  {
    // Check if the input you get is an integer
    if (std::cin >> column)
    {
      // Check if the integer is valid
      if (m_gameBoard.isMoveValid(column))
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
    std::cout << "We have a Winner!" << std::endl;
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