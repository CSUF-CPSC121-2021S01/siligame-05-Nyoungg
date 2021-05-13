#include "player.h"
#include <iostream>
#include "cpputils/graphics/image.h"

void Player::Draw(graphics::Image& image) {
  graphics::Color black(0, 0, 0);
  graphics::Color mt(255, 235, 205);
  graphics::Color grey(160, 160, 160);
  graphics::Color gray(70, 70, 70);

  image.DrawRectangle(GetX(), GetY(), GetWidth(), GetHeight(), gray);
  image.DrawRectangle(GetX() + 10, GetY() + 14, 30, 36, black);
  image.DrawRectangle(GetX() + 11, GetY() + 18, 28, 31, mt);
  image.DrawRectangle(GetX() + 23, GetY() + 4, 4, 35, black);
  image.DrawRectangle(GetX() + 24, GetY() + 5, 2, 34, grey);
  image.DrawRectangle(GetX() + 8, GetY() + 15, 34, 2, black);
  image.DrawRectangle(GetX() + 9, GetY() + 14, 32, 4, black);
  image.DrawRectangle(GetX() + 23, GetY() + 39, 2, 2, black);
  image.DrawRectangle(GetX() + 23, GetY() + 41, 1, 1, black);
  image.DrawRectangle(GetX() + 25, GetY() + 38, 1, 2, black);
  for (int i = 0; i < 7; i++) {
    if (i != 3)
      image.DrawRectangle(GetX() + (12 + (i * 4)), GetY() + 40, 2, 2, black);
  }
  for (int i = 0; i < 6; i++) {
    image.DrawRectangle(GetX() + (14 + (i * 4)), GetY() + 43, 2, 2, black);
  }
  for (int i = 0; i < 7; i++) {
    image.DrawRectangle(GetX() + (12 + (i * 4)), GetY() + 46, 2, 2, black);
  }
}

void Player::Move(const graphics::Image& img) {}

void PlayerProjectile::Draw(graphics::Image& image) {
  graphics::Color black(0, 0, 0);
  image.DrawRectangle(GetX(), GetY(), 5, 5, black);
}

void PlayerProjectile::Move(const graphics::Image& img) {
  if (GetIsActive()) {
    SetY(GetY() - 3);
  }
  if (IsOutOfBounds(img)) {
    SetIsActive(false);
  }
}
