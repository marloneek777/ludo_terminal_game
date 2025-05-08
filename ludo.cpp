#include<vector>
#include<iostream>
#include"ludo.h"
#include"random.h"
#include"display.h"
#include"input.h"

int Ludo::GameManager() {
  int result = -1;
  int numOfPlayers = 4;
  int current_player = 0;
  bool isGameOver = false;

  std::vector<Ludo::Player> players = CreatePlayers(numOfPlayers);
  std::vector<Token*> tokenPointers = CreatePointersToTokens(players);
  Board board; // 0 - 39 wich equals 40 tiles of main track you knowwwwww...

  for (const auto& player : players) {
    player.printPlayerStats();
  }


  game_actions action{ game_actions::INVALID_COMMAND };
  while (!isGameOver) {

      std::string input = Input::GetProcessedInput();

      if (input == "-roll" || input == "-r") {
        action = game_actions::ROLL;
      }
      else if (input == "-pass" || input == "-p") {
        action = game_actions::PASS;
      }
      else {
        action = game_actions::INVALID_COMMAND;
      }

      switch (action) {
      case game_actions::INVALID_COMMAND:
        break;
      case game_actions::ROLL:
        isGameOver = true;
        break;
      case game_actions::PASS:
        Ludo::SwitchPlayer(current_player, numOfPlayers);
        break;
      default:
        break;
      }
    }
  return result;
  }

void Ludo::SwitchPlayer(int& currentPlayer, int numOfPlayers) {
  currentPlayer = (currentPlayer + 1) % numOfPlayers;
}


std::vector<Ludo::Player> Ludo::CreatePlayers(int numOfPlayers) {
  std::vector<Ludo::Player> players;
  for (int i = 0; i < numOfPlayers; ++i) {
    Ludo::Player p(i);
    players.push_back(p);
  }
  return players;
}

std::vector<Ludo::Token*> Ludo::CreatePointersToTokens(const std::vector<Ludo::Player>& players) {
  std::vector<Ludo::Token*> tokenPointers;
  for (const auto& player : players) {
    for (const auto& token : player.tokens) {
      tokenPointers.push_back(const_cast<Ludo::Token*>(&token));
    }
  }
  return tokenPointers;
}