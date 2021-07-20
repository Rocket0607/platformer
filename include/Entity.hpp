#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Math.hpp"

class Entity {
public:
  Entity(Vector2f p_pos, Vector2f p_dimensions, SDL_Texture* p_tex);
  Vector2f& getPos() {
    return pos;
  }
  SDL_Texture* getTex();
  SDL_Rect getCurrentFrame();

protected:
  Vector2f pos;
  Vector2f dimensions;
  SDL_Rect currentFrame;
  SDL_Texture* tex;
};
