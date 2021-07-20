#include <SDL2/SDL.h>

#include "Player.hpp"

void Player::setPos(Vector2f& p_pos) {
  pos = p_pos;
}

void Player::update() {
  Vector2f newPos = getPos();
  newPos.x += xVel;
  newPos.y += yVel;
  setPos(newPos);
}
