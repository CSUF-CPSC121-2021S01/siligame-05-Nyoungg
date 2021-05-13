#include "game.h"
#include <iostream>
#include <vector>
#include "opponent.h"
#include "player.h"

void Game::RemoveInactive() {
  int count = 0;
  while (count < opponents.size()) {
    if (opponents[count]->GetIsActive() == false) {
      opponents.erase(opponents.begin() + count);
      count--;
    }
    count++;
  }

  count = 0;
  while (count < oppProjectile.size()) {
    if (oppProjectile[count]->GetIsActive() == false) {
      oppProjectile.erase(oppProjectile.begin() + count);
      count--;
    }
    count++;
  }

  count = 0;
  while (count < playerProjectile.size()) {
    if (playerProjectile[count]->GetIsActive() == false) {
      playerProjectile.erase(playerProjectile.begin() + count);
      count--;
    }
    count++;
  }
}

void Game::LaunchProjectiles() {
  for (int i = 0; i < opponents.size(); i++) {
    std::unique_ptr<OpponentProjectile> ptr =
        (opponents[i]->LaunchProjectile());
    if (ptr != nullptr) {
      oppProjectile.push_back(std::move(ptr));
    }
  }
}

void Game::CreateOpponents() {
  std::unique_ptr<Opponent> enemy(new Opponent(25, 25, 50, 50));
  opponents.push_back(std::move(enemy));
}

void Game::Init() {
  GetGameScreen().AddMouseEventListener(*this);
  GetGameScreen().AddAnimationEventListener(*this);
  player1.SetX(350);
  player1.SetY(400);
}

void Game::MoveGameElements() {
  for (int i = 0; i < opponents.size(); i++) {
    if (opponents[i]->GetIsActive()) {
      opponents[i]->Move(GetGameScreen());
    }
  }
  for (int i = 0; i < oppProjectile.size(); i++) {
    if (oppProjectile[i]->GetIsActive()) {
      oppProjectile[i]->Move(GetGameScreen());
    }
  }
  for (int i = 0; i < playerProjectile.size(); i++) {
    if (playerProjectile[i]->GetIsActive()) {
      playerProjectile[i]->Move(GetGameScreen());
    }
  }
}

void Game::FilterIntersections() {
  // if Player intersects with Opponents.
  for (int i = 0; i < opponents.size(); i++) {
    if (player1.GetIsActive() && opponents[i]->GetIsActive()) {
      if (opponents[i]->IntersectsWith(&player1)) {
        player1.SetIsActive(false);
        opponents[i]->SetIsActive(false);
        lost = true;
      }
    }
  }

  // if PlayerProjectile intersects with Opponents.
  for (int i = 0; i < playerProjectile.size(); i++) {
    for (int j = 0; j < opponents.size(); j++) {
      if (playerProjectile[i]->GetIsActive() && opponents[j]->GetIsActive()) {
        if (playerProjectile[i]->IntersectsWith(opponents[j].get())) {
          playerProjectile[i]->SetIsActive(false);
          opponents[j]->SetIsActive(false);
          if (player1.GetIsActive()) {
            score++;
          }
        }
      }
    }
  }

  // if OpponentProjectile intersects with Player.
  for (int i = 0; i < oppProjectile.size(); i++) {
    if (player1.GetIsActive() && oppProjectile[i]->GetIsActive()) {
      if (oppProjectile[i]->IntersectsWith(&player1)) {
        player1.SetIsActive(false);
        oppProjectile[i]->SetIsActive(false);
        lost = true;
      }
    }
  }
}

void Game::UpdateScreen() {
  // gamescreen.DrawRectangle(0, 0, gamescreen.GetWidth(),
  // gamescreen.GetHeight(), graphics::Color(70, 70, 70));
  if (lost == true) {
    player1.SetIsActive(false);
  }
  gamescreen.DrawText(0, 0, "Score: " + std::to_string(GetScore()), 30,
                      graphics::Color(255, 255, 255));
  if (HasLost()) {
    gamescreen.DrawText(235, 250, "GAME OVER", 70,
                        graphics::Color(255, 255, 255));
  }

  for (int i = 0; i < opponents.size(); i++) {
    if (opponents[i]->GetIsActive()) {
      opponents[i]->Draw(gamescreen);
    }
  }
  for (int i = 0; i < oppProjectile.size(); i++) {
    if (oppProjectile[i]->GetIsActive()) {
      oppProjectile[i]->Draw(gamescreen);
    }
  }
  for (int i = 0; i < playerProjectile.size(); i++) {
    if (playerProjectile[i]->GetIsActive()) {
      playerProjectile[i]->Draw(gamescreen);
    }
  }

  if (player1.GetIsActive()) {
    player1.Draw(gamescreen);
  }
}

void Game::OnAnimationStep() {
  if (opponents.size() == 0 && lost == false) {
    CreateOpponents();
  }
  MoveGameElements();
  LaunchProjectiles();
  FilterIntersections();
  RemoveInactive();
  UpdateScreen();
  gamescreen.Flush();
}

void Game::OnMouseEvent(const graphics::MouseEvent& event) {
  if (event.GetMouseAction() == graphics::MouseAction::kMoved ||
      event.GetMouseAction() == graphics::MouseAction::kDragged) {
    int oldX = player1.GetX();
    int oldY = player1.GetY();
    player1.SetX(event.GetX() - 25);
    player1.SetY(event.GetY() - 25);
    if (player1.IsOutOfBounds(GetGameScreen())) {
      player1.SetX(oldX);
      player1.SetY(oldY);
    }
  }
  if ((event.GetMouseAction() == graphics::MouseAction::kPressed || event.GetMouseAction() == graphics::MouseAction::kDragged) &&
      player1.GetIsActive() ) {
    std::unique_ptr<PlayerProjectile> ptr(
        new PlayerProjectile(player1.GetX() + 25, player1.GetY(), 5, 5));
    playerProjectile.push_back(std::move(ptr));
  }
}

void Game::Start() { gamescreen.ShowUntilClosed(); }
