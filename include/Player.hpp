#pragma once

#include "Math.hpp"
#include "Entity.hpp"

class Player: public Entity {
public:
  Player(Vector2f p_pos, Vector2f p_dimensions, SDL_Texture* p_tex):Entity(p_pos, p_dimensions, p_tex) {}
  void setPos(Vector2f& p_pos);
  void update();
  float xVel = 0.0f;
  float yVel = 0.0f;
};
