#ifndef GAME_ELEMENT_H
#define GAME_ELEMENT_H

#include "cpputils/graphics/image.h"

class GameElement {
 public:
  GameElement() : x_(0), y_(0), width_(50), height_(50) {}
  GameElement(const int& x, const int& y) : x_(x), y_(y) {}
  GameElement(const int& x, const int& y, const int& width, const int& height)
      : x_(x), y_(y), width_(width), height_(height) {}
  void SetX(const int& x) { x_ = x; }
  void SetY(const int& y) { y_ = y; }
  int GetX() const { return x_; }
  int GetY() const { return y_; }
  int GetWidth() const { return width_; }
  int GetHeight() const { return height_; }
  virtual void Draw(graphics::Image& image) = 0;
  virtual void Move(const graphics::Image& img) = 0;
  bool GetIsActive() { return is_active; }
  void SetIsActive(bool active) { is_active = active; }
  bool IntersectsWith(GameElement* object);
  bool IsOutOfBounds(const graphics::Image& image);

 protected:
  int x_;
  int y_;
  int width_;
  int height_;
  bool is_active = true;
};

#endif
