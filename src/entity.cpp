#include "Entity.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Entity::Entity(Vector2f p_pos, Vector2f p_dimensions, SDL_Texture* p_tex)
  :pos(p_pos), dimensions(p_dimensions), tex(p_tex)
{
  currentFrame.x = 0;
  currentFrame.y = 0;
  currentFrame.w = dimensions.x;
  currentFrame.h = dimensions.y;
}

SDL_Texture* Entity::getTex() {
  return tex;
}

SDL_Rect Entity::getCurrentFrame() {
  return currentFrame;
}
