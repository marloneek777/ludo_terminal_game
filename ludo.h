#pragma once
#include<string>
#include<iostream>
#include<vector>
#include<array>

namespace Ludo {

  struct Token {
    enum class TokenState { Home, Active, Base, Finished };
    int ID{};
    int ownerID{};
    int pos{};
    int basePos{};
    bool isSelected = false;
    TokenState state{ TokenState::Active };

    Token(int id, int owner) : ID(id), ownerID(owner) {}

    int getTokenID() const {
      return ID;
    }

    void Increment() {
      pos++;
    }

    bool Selected() const {
      return isSelected;
    }

    void setAsSelected() {
      isSelected = true;
    }

    void deselect() {
      isSelected = false;
    }

    int getPos() const {
      switch (state)
      {
      case TokenState::Active:
        return pos;
        break;
      case TokenState::Base:
        return basePos;
        break;
      default:
        break;
      }
      return -1;
    }

    int getOwnerID() const {
      return ownerID;
    }

    void returnHome() {
      state = TokenState::Home;
    }

    void activate() {
      state = TokenState::Active;
    }

    void moveToBase(int base_location) {
      state = TokenState::Base;
      pos = base_location;
    }

    void Finish() {
      state = TokenState::Finished;
    }

    bool isHome() const {
      return state == TokenState::Home;
    }

    bool isActive() const {
      return state == TokenState::Active;
    }

    bool isBase() const {
      return state == TokenState::Base;
    }

    bool hasFinished() const {
      return state == TokenState::Finished;
    }

    TokenState getState() const {
      return state;
    }

    std::string tokenStringState() const {
      switch (state)
      {
      case TokenState::Home:
        return "Home";
      case TokenState::Active:
        return "Active";
      case TokenState::Base:
        return "Base";
      default:
        return "Unknown";
      }
    }
  };

  struct Player {
    int ID{};
    int tokensInHome{ 4 };
    int tokensInBase{ 0 };
    int selectedTokenID{ 0 };
    bool hasWon = false;
    std::vector<Token> tokens;

    Player(int id) : ID(id) {
      for (int i = 0; i < 4; ++i) {
        tokens.emplace_back(i, ID);
      }
      updateTokenSelection();
    }


    void updateTokenSelection() {
      for (auto& token : tokens) {
        if (token.getTokenID() == selectedTokenID) {
          token.setAsSelected();
        }
        else {
          token.deselect();
        }
      }
    }

    bool isValidTokenID(int new_selection_ID) {
      for (const auto& token : tokens) {
        if (new_selection_ID == token.getTokenID()) {
          return true;
        }
      }
      return false;
    }

    void changeToken(int new_selection_ID) {
      if (isValidTokenID(new_selection_ID)) {
        selectedTokenID = new_selection_ID;
        updateTokenSelection();
      }
      else {
        std::cout << "token with this ID does not exist!";
      }
    }

    void moveSelectedToken() {
      for (auto& token : tokens) {
        if (token.Selected()) {
          token.Increment();
        }
      }
    }

    int getPlayerID() const {
      return ID;
    }

    void printPlayerStats() const {
      std::cout << "Player ID: " << ID << '\n';
      for (const auto& token : tokens) {
        std::cout << "Token: " << '[' << token.getTokenID() << ']' << " with owner ID: " << token.getOwnerID() << " is in state: " << token.tokenStringState() << '\n';
      }
    }
  };

  struct Tile {
    enum class TileState { Empty, Blocked, Safe };
    TileState state{ TileState::Empty };
    std::vector<Token*> tokensOnTile;

    int numOfTokensOnTile() const {
      return static_cast<int>(tokensOnTile.size());
    }

    void setStateToEmpty() {
      state = TileState::Empty;
    }

    void setStateToBlocked() {
      state = TileState::Blocked;
    }

    void setStateToSafe() {
      state = TileState::Safe;
    }

    bool isEmpty() const {
      return tokensOnTile.empty();
    }

    void clearTile() {
      tokensOnTile.clear();
      setStateToEmpty();
    }

  };

  struct PlayerBase {
    int baseLength{ 4 };
    std::vector<Tile> base;

    PlayerBase() {
      for (int i = 0; i < baseLength; ++i) {
        Tile t;
        base.push_back(t);
      }
    }

    void clear() {
      for (auto& tile : base) {
        tile.clearTile();
      }
    }
  };

  struct Board {
    int mainTrackLength{ 40 };
    int baseCount{ 4 };
    std::vector<Tile> MainTrack;
    std::vector<PlayerBase> Bases;

    Board() {
      for (int i = 0; i < mainTrackLength; ++i) {
        Tile t;
        MainTrack.push_back(t);
      }
      for (int i = 0; i < baseCount; ++i) {
        PlayerBase b;
        Bases.push_back(b);
      }
    }

    void clearMainTrack() {
      for (auto& tile : MainTrack) {
        tile.clearTile();
      }
    }

    void clearBases() {
      for (auto& base : Bases) {
        base.clear();
      }
    }

    void updateBoard(const std::vector<Ludo::Token*>& tokenPtr) {
      for (const auto& token : tokenPtr) {
        if (token->isHome() || token->hasFinished()) {
          continue;
        }
        else if (token->isActive()) {
          int pos = token->getPos();
          MainTrack[pos].tokensOnTile.push_back(token);
        }
        else if (token->isBase()) {
          int pos = token->getPos();
          Bases[token->getOwnerID()].base[pos].tokensOnTile.push_back(token);
        }
      }
    }

  };

  enum class game_actions { INVALID_COMMAND, ROLL, PASS };
  int GameManager();
  std::vector<Ludo::Player> CreatePlayers(int numOfPlayers);
  std::vector<Ludo::Token*> CreatePointersToTokens(const std::vector<Ludo::Player>& players);
  void SwitchPlayer(int& currentPlayer, int numOfPlayers);

}