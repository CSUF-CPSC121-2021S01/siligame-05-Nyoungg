#ifndef OPPONENT_H
#define OPPONENT_H

#include "cpputils/graphics/image.h"
#include "game_element.h"

class Opponent : public GameElement {
 public:
  Opponent() : GameElement() {}
  Opponent(int x, int y) : GameElement(x, y, 50, 50) {}
  Opponent(int x, int y, int width, int height)
      : GameElement(x, y, width, height) {}
  void Draw(graphics::Image& image) override;
  void Move(const graphics::Image& img) override;
  std::unique_ptr<class OpponentProjectile> LaunchProjectile();
  int counter = 0;
};

class OpponentProjectile : public GameElement {
 public:
  OpponentProjectile() : GameElement() {}
  OpponentProjectile(int x, int y) : GameElement(x, y, 5, 5) {}
  OpponentProjectile(int x, int y, int width, int height)
      : GameElement(x, y, width, height) {}
  void Draw(graphics::Image& image) override;
  void Move(const graphics::Image& img) override;
};

#endif
