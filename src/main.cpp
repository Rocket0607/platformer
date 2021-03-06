#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <iostream>
#include <vector>

#include "Entity.hpp"
#include "Math.hpp"
#include "Player.hpp"
#include "RenderWindow.hpp"
#include "Utils.hpp"

void initSDL() {
  if (SDL_Init(SDL_INIT_VIDEO) > 0)
    std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError()
              << std::endl;

  if (!(IMG_Init(IMG_INIT_PNG)))
    std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;
}

void createGround(std::vector<Entity>& p_entities,
                  int p_startx,
                  int p_starty,
                  int p_numOfBlocks,
                  SDL_Texture* p_tex) {
  int sizeOfBlock = 32;
  for (int i = 0; i < p_numOfBlocks; i++) {
    Vector2f pos(p_startx + sizeOfBlock * i, p_starty);
    Vector2f dimensions(sizeOfBlock, sizeOfBlock);
    Entity e(pos, dimensions, p_tex);
    p_entities.push_back(e);
  }
}

Entity createSky(SDL_Texture* p_tex) {
  Vector2f pos(0, 0);
  Vector2f dimensions(640, 360);
  Entity sky(pos, dimensions, p_tex);
  return sky;
}

int main(int argc, char* args[]) {
  initSDL();

  int windowWidth = 1280;
  int windowHeight = 720;
  const char* windowTitle = "GAME v1.0";
  RenderWindow window(windowTitle, windowWidth, windowHeight);

  SDL_Texture* grassTexture = window.loadTexture("res/gfx/ground_grass_1.png");
  SDL_Texture* skyTexture = window.loadTexture("res/gfx/sky.png");
  SDL_Texture* knightTexture = window.loadTexture("res/gfx/knight.png");

  std::vector<Entity> entities;
  createGround(entities, 0, windowHeight / 2 - 32, windowWidth / 32,
               grassTexture);
  Entity sky = createSky(skyTexture);

  Vector2f pos(0, 0);
  Vector2f dimensions(32, 32);
  Player knight(pos, dimensions, knightTexture);

  bool gameRunning = true;

  const float timeStep = 0.01f;
  float accumulator = 0.0f;
  float currentTime = utils::hireTimeInSeconds();

  SDL_Event event;

  while (gameRunning) {
    // SDL_Rect knightBox = knight.getCurrentFrame();
    // SDL_Rect* knightBoxPointer = &knightBox;
    // SDL_Rect groundBox = entities[0].getCurrentFrame();
    // SDL_Rect* groundBoxPointer = &groundBox;

    // SDL_bool isTouchingGround = SDL_HasIntersection(knightBoxPointer, groundBoxPointer);
    // std::cout << isTouchingGround << std::endl;

    int startTicks = SDL_GetTicks();

    float newTime = utils::hireTimeInSeconds();
    float frameTime = newTime - currentTime;
    currentTime = newTime;

    accumulator += frameTime;

    while (accumulator >= timeStep) {
      // Get our controls and events
      while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
          gameRunning = false;
        }
        if (event.type == SDL_KEYDOWN) {
          switch (event.key.keysym.sym) {
            case SDLK_a:
              knight.xVel -= 0.75;
              break;
            case SDLK_d:
              knight.xVel += 1.0;
              break;
            case SDLK_SPACE:
              knight.yVel -= 5.0;
              break;
          }
        }
	else if (event.type == SDL_KEYUP) {
          switch (event.key.keysym.sym) {
            case SDLK_a:
              knight.xVel = 0.0;
              break;
            case SDLK_d:
              knight.xVel = 0.0;
              break;
          }
	}
      }

      if (knight.xVel > 3.5) 
        knight.xVel -= 0.5;

      if (knight.xVel < -3.5) 
        knight.xVel += 0.5;

      if (knight.getPos().y < 296)
        knight.yVel += 0.2;

      else if (knight.getPos().y > 296) {
        knight.yVel = 0.0;
	Vector2f newPos(knight.getPos().x, 296);
	knight.setPos(newPos);
      }

      knight.update();

      window.clear();

      window.render(sky);
      window.render(knight);
      for (Entity& e : entities) {
        window.render(e);
      }
      accumulator -= timeStep;
    }

    // const float alpha = accumulator / timeStep;

    window.display();
    int frameTicks = SDL_GetTicks() - startTicks;

    if (frameTicks < 1000 / window.getRefreshRate())
      SDL_Delay(1000 / window.getRefreshRate());
  }

  window.cleanUp();
  SDL_Quit();

  return 0;
}
