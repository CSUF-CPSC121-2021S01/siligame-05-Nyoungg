#ifndef PLAYER_H
#define PLAYER_H

#include "cpputils/graphics/image.h"
#include "game_element.h"
#include "opponent.h"

class Player : public GameElement {
 public:
  Player() : GameElement() {}
  Player(int x, int y) : GameElement(x, y, 50, 50) {}
  Player(int x, int y, int width, int height)
      : GameElement(x, y, width, height) {}
  void Draw(graphics::Image& image) override;
  void Move(const graphics::Image& img) override;
};

class PlayerProjectile : public GameElement {
 public:
  PlayerProjectile() : GameElement() {}
  PlayerProjectile(int x, int y) : GameElement(x, y, 5, 5) {}
  PlayerProjectile(int x, int y, int width, int height)
      : GameElement(x, y, width, height) {}
  void Draw(graphics::Image& image) override;
  void Move(const graphics::Image& img) override;
};

#endif
