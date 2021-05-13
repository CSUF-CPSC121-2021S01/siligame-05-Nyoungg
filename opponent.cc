#include "opponent.h"
#include <iostream>
#include <memory>
#include "cpputils/graphics/image.h"

std::unique_ptr<class OpponentProjectile> Opponent::LaunchProjectile() {
  if (counter == 0) {
    counter = 10;
    std::unique_ptr<OpponentProjectile> ptr(
        new OpponentProjectile(GetX() + 25, GetY() + 50, 5, 5));
    return std::move(ptr);
  }
  counter--;
  return nullptr;
}

void Opponent::Draw(graphics::Image& image) {
  graphics::Color black(0, 0, 0);
  graphics::Color brown(139, 69, 19);
  graphics::Color white(255, 255, 255);
  graphics::Color gray(70, 70, 70);

  image.DrawRectangle(GetX(), GetY(), GetWidth(), GetHeight(), gray);
  image.DrawRectangle(GetX() + 11, GetY() + 4, 28, 3, black);
  image.DrawRectangle(GetX() + 7, GetY() + 7, 36, 4, black);
  image.DrawRectangle(GetX() + 10, GetY() + 11, 30, 39, black);
  image.DrawRectangle(GetX() + 11, GetY() + 11, 28, 7, white);
  image.DrawRectangle(GetX() + 11, GetY() + 19, 28, 17, brown);
  image.DrawRectangle(GetX() + 11, GetY() + 37, 28, 12, white);
}

void Opponent::Move(const graphics::Image& img) {
  if (GetIsActive()) {
    SetY(GetY() + 1);
    SetX(GetX() + 1);
  }
  if (IsOutOfBounds(img)) {
    SetIsActive(false);
  }
}

void OpponentProjectile::Draw(graphics::Image& image) {
  graphics::Color darkBrown(102, 51, 0);
  image.DrawRectangle(GetX(), GetY(), 5, 5, darkBrown);
}

void OpponentProjectile::Move(const graphics::Image& img) {
  if (GetIsActive()) {
    SetY(GetY() + 1);
    SetX(GetX() + 1);
  }
  if (IsOutOfBounds(img)) {
    SetIsActive(false);
  }
}
