#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include "cpputils/graphics/image.h"
#include "opponent.h"
#include "player.h"

class Game : public graphics::AnimationEventListener,
             public graphics::MouseEventListener {
 public:
  Game() : gamescreen(800, 600), player1(0, 0, 50, 50) {}
  Game(int width, int height) : gamescreen(width, height) {}
  Game(int width, int height, int x, int y, int width2, int height2)
      : gamescreen(width, height), player1(x, y, width2, height2) {}
  graphics::Image& GetGameScreen() { return gamescreen; }
  std::vector<std::unique_ptr<Opponent>>& GetOpponents() { return opponents; }
  std::vector<std::unique_ptr<OpponentProjectile>>& GetOpponentProjectiles() {
    return oppProjectile;
  }
  std::vector<std::unique_ptr<PlayerProjectile>>& GetPlayerProjectiles() {
    return playerProjectile;
  }
  Player& GetPlayer() { return player1; }
  void CreateOpponents();
  void CreateOpponentProjectiles();
  void CreatePlayerProjectiles();
  void Init();
  void UpdateScreen();
  void Start();
  void MoveGameElements();
  void FilterIntersections();
  void OnAnimationStep();
  void OnMouseEvent(const graphics::MouseEvent& event);
  int GetScore() { return score; }
  bool HasLost() { return lost; }
  void LaunchProjectiles();
  void RemoveInactive();

 private:
  graphics::Image gamescreen;
  std::vector<std::unique_ptr<Opponent>> opponents;
  std::vector<std::unique_ptr<OpponentProjectile>> oppProjectile;
  std::vector<std::unique_ptr<PlayerProjectile>> playerProjectile;
  Player player1;
  int score = 0;
  bool lost = false;
};

#endif
