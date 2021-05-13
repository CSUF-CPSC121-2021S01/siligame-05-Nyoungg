#include "game_element.h"
#include <iostream>
#include "cpputils/graphics/image.h"

bool GameElement::IntersectsWith(GameElement* object) {
  int x1 = GetX();
  int y1 = GetY();
  int w1 = GetWidth();
  int h1 = GetHeight();
  int x2 = object->GetX();
  int y2 = object->GetY();
  int w2 = object->GetWidth();
  int h2 = object->GetHeight();

  return x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2;
}

bool GameElement::IsOutOfBounds(const graphics::Image& image) {
  int x = GetX();
  int y = GetY();
  int w = GetWidth();
  int h = GetHeight();

  if (x < 0) {
    return true;
  }
  if (x + w > image.GetWidth()) {
    return true;
  }
  if (y < 0) {
    return true;
  }
  if (y + h > image.GetHeight()) {
    return true;
  }

  return false;
}
